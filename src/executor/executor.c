/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:34:47 by rbarbier          #+#    #+#             */
/*   Updated: 2024/03/14 11:04:20 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	wait_processes(pid_t *pid, int *ret_value, int n_cmds)
{
	int	status;
	int	i;

	i = 0;
	while (i < n_cmds)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			*ret_value = WEXITSTATUS(status);
		i++;
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			*ret_value = 131;
			ft_fprintf(2, "Quit: %d\n", WTERMSIG(status));
		}
		else if (WTERMSIG(status) == SIGINT)
			*ret_value = 130;
	}
}

void	init_data(t_pipe *data, t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	data->n_cmds = i;
	data->pipe_ends[0] = -1;
	data->pipe_ends[1] = -1;
	data->infile_fd = 0;
	data->outfile_fd = 0;
	data->cmd = NULL;
	data->pid = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pid)
		msg_exit(0, 0, ERR_MALLOC, 1);
}

void	breeder(t_cmd *cmd, t_env **env, t_env **exp, t_pipe data)
{
	int	i;
	int	ret_value;

	i = 0;
	init_signals(0);
	while (cmd)
	{
		if (cmd->next)
			if (pipe(data.pipe_ends))
				msg_exit(0, 0, ERR_PIPE, 1);
		data.pid[i] = fork();
		if (data.pid[i] == -1)
			msg_exit(0, 0, ERR_FORK, 1);
		if (data.pid[i] == 0)
			child(data, cmd, env, exp);
		dup2(data.pipe_ends[0], STDIN_FILENO);
		close_pipes(data.pipe_ends[0], data.pipe_ends[1]);
		cmd = cmd->next;
		i++;
	}
	reset_original_stds(&data);
	wait_processes(data.pid, &ret_value, data.n_cmds);
	init_signals(1);
	exit_status(ret_value);
}

int	builtin_check(char *str)
{
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "echo") || !ft_strcmp(str,
			"cd") || !ft_strcmp(str, "env") || !ft_strcmp(str, "exit")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "export"))
		return (1);
	return (0);
}

// if the command is a builtin and there is no pipe
void	executor(t_cmd *cmd, t_env **env, t_env **exp)
{
	t_pipe	data;

	init_data(&data, cmd);
	save_original_stds(&data);
	if (cmd->args != NULL && builtin_check(*cmd->args) && !cmd->next)
	{
		if (get_files_redir(cmd->redir, &data))
			return ;
		make_redirections(&data, cmd);
		is_builtin(cmd->args, env, exp);
		reset_original_stds(&data);
		free(data.pid);
		return ;
	}
	breeder(cmd, env, exp, data);
	unlink_heredoc(cmd);
	free(data.pid);
}

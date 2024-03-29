/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:04:40 by rbarbier          #+#    #+#             */
/*   Updated: 2024/03/14 11:11:27 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(char **cmd, t_env **env, t_env **exp)
{
	if (cmd == NULL)
		return (exit_status(1), 1);
	if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd(cmd);
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd);
	else if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(env, exp, cmd);
	else if (!ft_strcmp(cmd[0], "env"))
		ft_env(env, cmd);
	else if (!ft_strcmp(cmd[0], "exit"))
		ft_exit(cmd);
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(env, exp, cmd);
	else if (!ft_strcmp(cmd[0], "export"))
		ft_export(exp, env, cmd);
	else
		return (0);
	return (1);
}

void	is_local_cmd(t_cmd *cmd, t_pipe data, char **envp)
{
	if (cmd->args == NULL)
		exit (1);
	if (ft_strchr(cmd->args[0], '/') || data.cmd_paths == NULL
		|| data.cmd_paths[0] == NULL)
	{
		if (check_absolute_path(cmd))
		{
			execve(cmd->args[0], cmd->args, envp);
			ft_fprintf(2, "%s:  command incorrect\n", cmd->args[0]);
			exit(1);
		}
		msg_exit(cmd->args[0], 0, ERR_CMD_NOT_FOUND, 1);
	}
}

void	is_global_cmd(t_cmd *cmd, t_pipe data, char **envp)
{
	if (check_paths(&data, cmd))
	{
		execve(data.cmd, cmd->args, envp);
		ft_fprintf(2, "%s:  command incorrect\n", cmd->args[0]);
		exit(1);
	}
	msg_exit(cmd->args[0], 0, ERR_CMD_NOT_FOUND, 127);
}

void	unlink_heredoc(t_cmd *cmd)
{
	t_rd	*tmp;

	tmp = cmd->redir;
	while (cmd)
	{
		while (tmp)
		{
			if (tmp->type && tmp->type == HEREDOC)
				unlink(tmp->file);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
}

void	child(t_pipe data, t_cmd *cmd, t_env **env, t_env **exp)
{
	char	**envp;

	if (cmd->args == NULL)
		return ;
	if (cmd->args[0][0] == 0)
		return (ft_fprintf(2, NOTFOUND, cmd->args[0]), exit(127));
	envp = env_to_array(env);
	init_signals(0);
	get_files_redir(cmd->redir, &data);
	make_redirections(&data, cmd);
	data.cmd_paths = get_paths(env);
	if (is_builtin(cmd->args, env, exp))
		exit(exit_status(0));
	is_local_cmd(cmd, data, envp);
	is_global_cmd(cmd, data, envp);
}

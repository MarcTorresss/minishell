/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:34:47 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/18 17:34:30 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_data(t_pipe *data)
{
	t_cmd	*tmp;
	int i;

	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	data->n_cmds = i;
	data->pipe_ends[0] = -1;
	data->pipe_ends[1] = -1;
	data->pid = malloc(sizeof(pid_t) * data->n_cmds);
	if (!data->pid)
		msg_exit(ERR_MALLOC, 0, 1);
}

void	breeder(t_cmd *cmd, t_env **env, t_env **exp)
{
	t_pipe	data;
	int		i;
	int		ret_value;

	init_data(&data);
	save_original_stds(&data);
	i = 0;
	while (cmd)
	{
		if (cmd->next)
			if (pipe(data.pipe_ends))
				msg_exit(ERR_PIPE, 0, 1);
		data.pid[i] = fork();
		if (data.pid[i] == -1)
			msg_exit(ERR_FORK, 0, 1);
		if (data.pid[i] == 0)
			child(data, cmd, env, exp);
		dup2(data.pipe_ends[0], STDIN_FILENO); // redirect INPUT for the next process
		close_pipes(data.pipe_ends[0], data.pipe_ends[1]);
		cmd = cmd->next;
		i++;
	}
	wait_processes(data.pid, &ret_value);
	reset_original_stds(&data);
	set_exit_status(ret_value);
}

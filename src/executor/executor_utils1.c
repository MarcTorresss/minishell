/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:41:44 by rbarbier          #+#    #+#             */
/*   Updated: 2024/03/11 15:27:42 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**env_to_array(t_env **env)
{
	int		i;
	char	**envp;
	t_env	*tmp;

	i = 0;
	tmp = *env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp)
		msg_exit(0, 0, ERR_MALLOC, 1);
	i = 0;
	tmp = *env;
	while (tmp)
	{
		envp[i] = ft_strjoin(tmp->name, "=");
		envp[i] = ft_join_n_destroy(envp[i], tmp->value, 1);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	save_original_stds(t_pipe *data)
{
	data->original_stdin = dup(STDIN_FILENO);
	data->original_stdout = dup(STDOUT_FILENO);
}

void	reset_original_stds(t_pipe *data)
{
	dup2(data->original_stdin, STDIN_FILENO);
	dup2(data->original_stdout, STDOUT_FILENO);
	close(data->original_stdin);
	close(data->original_stdout);
}

void	close_pipes(int fd1, int fd2)
{
	if (fd1 != -1)
	{
		close(fd1);
		fd1 = -1;
	}
	if (fd2 != -1)
	{
		close(fd2);
		fd2 = -1;
	}
}

void	check_file(char *file, int mode)
{
	if (mode == 1) // input
	{
		if (access(file, F_OK) != 0)
			msg_exit(file, 0, ERR_NO_FILE, 1);
		if (access(file, R_OK) != 0)
			msg_exit(file, 0, ERR_NO_PERM, 1);
	}
	else if (mode == 2)
	{
		if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
			msg_exit(file, 0, ERR_NO_PERM, 1);
	}
}

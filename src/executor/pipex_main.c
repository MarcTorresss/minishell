/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:34:47 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/16 17:01:24 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/*
pipe ends:
fd[0] read end
fd[1] write end
*/
char	*find_path(char **envp, char **argv)
{
	while (ft_strncmp("PATH", *envp, 4))
	{
		envp++;
		if (!envp || !*envp)
		{
			write(2, "minishell: ", 7);
			write(2, argv[2], ft_strlen(argv[2]));
			write(2, ": command not found\n", 20);
			write(2, "minishell: ", 7);
			write(2, argv[3], ft_strlen(argv[3]));
			write(2, ": command not found\n", 20);
			exit(127);
		}
	}
	return (*envp + 5);
}

void	pipe_end_check(int *pipe_end, int child)
{
	if (child == 1)
	{
		if (pipe_end[0] != -1)
			close(pipe_end[0]);
	}
	else // child == 2
	{
		if (pipe_end[1] != -1)
			close(pipe_end[1]);
	}
}

char	*find_path(t_env **env, char *name)
{
	t_env	*tmp_env;
	char	*path;

	tmp_env = find_env(env, "PATH");
	if (!tmp_env)
		return (0);
	path = ft_strdup(tmp_env->value);
	if (!path)
		error_pipex(7, 0);
	return (path);
}

void pipex_main(t_cmd *cmd, t_env **env, t_env **exp, t_exec *exec)
{
	(void)cmd;
	(void)env;
	(void)exp;
	int ret;

	if (pipe(exec->pipe_end) == -1)
		error_pipex(5, 0);
	exec->path = find_path(env, "PATH");
	exec->cmd_paths = ft_split(exec->path, ':');
	exec->indx = -1;
	while (exec->pipe[++(exec.indx)])
	exec->pid1 = fork();
	if (exec->pid1 < 0)
		error_pipex(6, 0);
	if (exec->pid1 == 0)
		first_child(exec, env);
	exec->pid2 = fork();
	if (exec->pid2 < 0)
		error_pipex(6, 0);
	if (exec->pid2 == 0)
		second_child(argv, *exec, envp);
	close(exec->pipe_end[0]);
	close(exec->pipe_end[1]);
	waitpid(exec->pid1, NULL, 0);
	waitpid(exec->pid2, &ret, 0);
	exit(WEXITSTATUS(ret));
}
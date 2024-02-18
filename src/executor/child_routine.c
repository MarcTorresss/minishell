/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 13:04:40 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/18 18:20:35 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*check_paths(t_pipe data, t_env *env, t_cmd *cmd)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (data.cmd_paths[i])
	{
		tmp = ft_strjoin("/", cmd->args[0]);
		path = ft_strjoin(data.cmd_paths[i], tmp);
		if (!tmp || !path)
			msg_exit(ERR_MALLOC, 0, 1);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
				return (path); // return the valid path to the command
			msg_exit(ERR_NO_PERM, cmd->args[0], 1);
		}
		free(tmp);
		free(path);
		i++;
	}
	return (NULL);
}

int	check_absolute_path(t_cmd *cmd)
{
	if (access(cmd->args[0], F_OK) == 0)
	{
		if (access(cmd->args[0], X_OK) == 0)
			return (1);
		msg_exit(ERR_NO_PERM, cmd->args[0], 1);
	}
	return (0);
}

void	get_paths(t_pipe *data, t_env *env)
{
	t_env	*tmp_env;

	tmp_env = find_env(&env, "PATH");
	if (!tmp_env)
		msg_exit(ERR_NO_PATH, 0, 1); // NEED TO BE FIXED
	data->cmd_paths = ft_split(tmp_env->value, ':');
	if (!data->cmd_paths)
		msg_exit(ERR_MALLOC, 0, 1);
}

void	child(t_pipe data, t_cmd *cmd, t_env **env, t_env **exp)
{
	char	**envp;

	get_files_redir(cmd->redirect, &data);
	make_redirections(data, cmd, env);
	if (is_builtin(cmd->args, env, exp));
		return ; // if the command is a builtin, execute it and return
	get_paths(&data, env);
	data.cmd = check_paths(data, env, cmd->args);
	envp = env_to_array(env);
	if (data.cmd)
		execve(data.cmd, cmd->args, envp);
	else if (check_absolute_path(cmd))
		execve(cmd->args[0], cmd->args, envp);
	else
		msg_exit(ERR_CMD_NOT_FOUND, cmd->args[0], 1);
	ft_fprintf(2, "%s: illegal option -- %c\n", cmd->args[0], cmd->args[0][1]);
	exit(1);
	// free(envp); do i need to free envp?
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:58:04 by rbarbier          #+#    #+#             */
/*   Updated: 2024/03/05 14:39:01 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_paths(t_pipe *data, t_cmd *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (data->cmd_paths[i])
	{
		path = ft_strjoin("/", cmd->args[0]);
		path = ft_join_n_destroy(data->cmd_paths[i], path, 2);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == 0)
			{
				data->cmd = path;
				return (1);
			}
			msg_exit(cmd->args[0], 0, ERR_NO_PERM, 1);
		}
		free(path);
		i++;
	}
	return (0);
}

int	check_absolute_path(t_cmd *cmd)
{
	if (access(cmd->args[0], F_OK) == 0)
	{
		if (access(cmd->args[0], X_OK) == 0)
			return (1);
		msg_exit(cmd->args[0], 0, ERR_NO_PERM, 1);
	}
	return (0);
}

char	**get_paths(t_env **env)
{
	t_env	*tmp_env;

	tmp_env = find_env(env, "PATH");
	if (!tmp_env)
		return (NULL);
	return (ft_split(tmp_env->value, ':'));
}

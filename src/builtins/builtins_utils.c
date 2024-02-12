/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:20:47 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/12 15:49:48 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env_del(t_env *env)
{
	//free(env->name);
	free(env);
	env = NULL;
}

t_env	*find_env(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	try_path(char *path)
{
	char	*msg;

	msg = ft_strjoin("minishell: cd: ", path);
	if (chdir(path))
	{
		perror(msg);
		////g_exit = 1;
		free(msg);
	}
	else
	{
		////g_exit = 0;
		free(msg);
		return (1);
	}
	return (0);
}

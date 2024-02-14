/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:20:47 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/14 11:05:33 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env_del(t_env *env)
{
	if (env->name)
		free(env->name);
	if (env->value)
		free(env->value);
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
		exit_value(1);
		free(msg);
	}
	else
	{
		exit_value(0);
		free(msg);
		return (1);
	}
	return (0);
}

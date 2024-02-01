/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:18:02 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/01 16:26:36 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	new_env_var(char *name, char *value, t_env **env_var)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->name = name;
	new->value = value;
	new->next = NULL;
	if (!*env_var)
		*env_var = new;
	else
	{
		tmp = *env_var;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}

void	init_envd(char **envd, t_env **env_var)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (envd[i])
	{
		name = ft_substr(envd[i], 0, ft_strchr(envd[i], '=') - envd[i]);
		value = getenv(name);
		if (!new_env_var(name, value, env_var))
			return ;
		i++;
	}
}

char	*find_env_var(char *name, t_env **env_var)
{
	t_env	*tmp;

	tmp = *env_var;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

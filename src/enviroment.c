/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 11:18:02 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/06 14:06:34 by rbarbier         ###   ########.fr       */
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
	new->name = ft_strdup(name);
	new->value = NULL;
	if (value)
		new->value = ft_strdup(value);
	new->next = NULL;
	new->prev = NULL;
	if (!*env_var)
		*env_var = new;
	else
	{
		tmp = *env_var;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	return (1);
}

void	init_SHLVL(t_env **env, t_env **exp)
{
	t_env	*tmp;

	tmp = find_env(exp, "SHLVL");
	if (tmp && tmp->value && ft_isdigit(tmp->value[0]))
		(tmp->value)++;
	ft_export(exp, env, " SHLVL=1");
}

void	init_envd(char **envd, t_env **env, t_env **exp)
{
	char	*name;
	char	*value;
	int		i;

	i = 0;
	while (envd[i])
	{
		name = ft_substr(envd[i], 0, ft_strchr(envd[i], '=') - envd[i]);
		value = getenv(name);
		new_env_var(name, value, env);
		new_env_var(name, value, exp);
		i++;
	}
	init_SHLVL(env, exp);
}

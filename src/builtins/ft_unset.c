/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:36:16 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/13 18:44:48 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	 remove_from_env(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = *env;
	if (!tmp)
		return ;
	if (!ft_strcmp(tmp->name, name))
	{
		*env = tmp->next;
		tmp->prev = NULL;
		ft_env_del(tmp);
	}
	else
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, name))
			{
				tmp->prev->next = tmp->next;
				if (tmp->next)
					tmp->next->prev = tmp->prev;
				ft_env_del(tmp);
			}
			tmp = tmp->next;
		}
	}
}

void	ft_unset(t_env **env, t_env **exp, char *input)
{
	int		i;
	char	*name;

	i = 0;
	if (ft_strlen(input) <= 6)
		return ;
	input += 6;
	while (input[i] != ' ' && input[i])
		i++;
	name = ft_substr(input, 0, i);
	remove_from_env(env, name);
	remove_from_env(exp, name);
	free(name);
	exit_value(0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:36:16 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/14 13:19:50 by rbarbier         ###   ########.fr       */
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

void	ft_unset(t_env **env, t_env **exp, char **cmd)
{
	int		i;
	int		j;
	char	*name;

	i = 0;
	if (!cmd[1])
		return ;
	while (cmd[++i])
	{
		j = 0;
		while (cmd[i][j] && (ft_isalnum(cmd[i][j]) || cmd[i][j] == '_'))
			j++;
		if (cmd[i][j] || !ft_isdigit(cmd[i][0]))
		{
			ft_fprintf(2, "minishell: unset: `%s': not a valid identifier\n", cmd[i]);
			exit_value(1);
			return ;
		}
		name = ft_strdup(cmd[i]);
		remove_from_env(env, name);
		remove_from_env(exp, name);
		free(name);
		exit_value(0);
	}
}

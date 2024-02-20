/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:05:17 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/20 16:34:26 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_env **env, char **cmd)
{
	t_env	*tmp;

	tmp = *env;
	if (cmd[1])
		msg_exit(0, 0, "env: too many arguments\n", 1);
	while (tmp)
	{ 
		ft_fprintf(1, "%s=", tmp->name);
		if (tmp->value)
			ft_fprintf(1, "%s\n", tmp->value);
		tmp = tmp->next;
	}
	exit_status(0);
}
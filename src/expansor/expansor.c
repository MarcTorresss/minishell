/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:08:37 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/08 13:38:59 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_env(t_cmd *cmd, t_env *env)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (cmd->args[i])
	{
		tmp = cmd->args[i];
		if (cmd->args[i][0] == '$')
		{
			tmp2 = ft_strdup(cmd->args[i] + 1);
			free(cmd->args[i]);
			cmd->args[i] = ft_strdup(find_env(env, tmp2)->value);
			free(tmp2);
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:02:05 by rbarbier          #+#    #+#             */
/*   Updated: 2024/03/12 17:10:40 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(char **cmd)
{
	char	*tmp;

	if (cmd && cmd[1])
		return (msg_return("pwd", 0, "too many arguments", 1));
	tmp = getcwd(NULL, 0);
	ft_fprintf(1, "%s\n", tmp);
	free(tmp);
	exit_status(0);
}

void	export_print(t_env **exp)
{
	t_env	*tmp;

	tmp = *exp;
	while (tmp)
	{
		ft_fprintf(1, "declare -x %s", tmp->name);
		if (tmp->value)
			ft_fprintf(1, "=\"%s\"\n", tmp->value);
		else
			ft_fprintf(1, "\n");
		tmp = tmp->next;
	}
}

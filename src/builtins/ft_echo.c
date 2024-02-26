/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:14:58 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/26 19:09:31 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		n_flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_fprintf(1, "%s", args[i]);
		if (args[i + 1])
			ft_fprintf(1, " ");
		i++;
	}
	if (!n_flag)
		ft_fprintf(1, "\n");
	exit_status(0);
}

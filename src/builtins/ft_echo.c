/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:14:58 by rbarbier          #+#    #+#             */
/*   Updated: 2024/03/06 16:33:32 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_sintax(char **args, int j)
{
	int	i;

	i = 1;
	if (args[j][0] != '-')
		return (0);
	while (args[j][i])
	{
		if (args[j][i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	check_n_flags(char **args, int *n_flag)
{
	int	i;

	i = 1;
	*n_flag = 0;
	while (args[i] && check_sintax(args, i))
	{
		*n_flag = 1;
		i++;
	}
	return (i);
}

void	ft_echo(char **args)
{
	int	i;
	int	n_flag;

	n_flag = 0;
	i = check_n_flags(args, &n_flag);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:14:58 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/06 16:53:41 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(t_env **exp, char *input)
{
	if (*exp)
	{
		if (ft_strcmp(input, "$?"))
			ft_printf("%d\n", g_exit);
		else
			ft_printf("%s\n", input);
	}
	g_exit = 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:14:58 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/12 15:50:34 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(t_env **exp, char *input)
{
	if (*exp)
	{
		if (ft_strcmp(input, "$?"))
			printf("%d\n", 0);//g_exit);
		else
			printf("%s\n", input);
	}
	//g_exit = 0;
}
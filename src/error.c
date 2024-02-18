/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:24:45 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/18 18:06:06 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error_msg(char *msg, int status)
{
	ft_putstr_fd(msg, 2);
	exit_value(status);
}

void	msg_exit(char *msg, char *arg, int status)
{
	if (arg)
		ft_fprintf(2, "error: '%s': %s\n", msg, arg);
	else
		ft_fprintf(2, "error: %s\n", msg);
	exit(status);
}

int	exit_value(int value)
{
	static int	prev = 0;
	int			ret;

	ret = prev;
	prev = value;
	return (ret);
}

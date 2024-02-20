/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:24:45 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/20 16:40:45 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	msg_return(char *cmd, char *arg, char *msg, int status)
{
	if (cmd && arg)
		ft_fprintf(2, "error: %s: '%s': %s\n", cmd, arg, msg);
	else if (cmd)
		ft_fprintf(2, "error: %s: %s\n", cmd, msg);
	else
		ft_fprintf(2, "error: %s\n", msg);
	exit_status(status);
}

void	msg_exit(char *cmd, char *arg, char *msg, int status)
{
	if (cmd && arg)
		ft_fprintf(2, "error: %s: '%s': %s\n", cmd, arg, msg);
	else if (cmd)
		ft_fprintf(2, "error: %s: %s\n", cmd, msg);
	else
		ft_fprintf(2, "error: %s\n", msg);
	exit(status);
}

int	exit_status(int value)
{
	static int	prev = 0;
	int			ret;

	ret = prev;
	prev = value;
	return (ret);
}

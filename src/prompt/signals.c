/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:20:13 by marvin            #+#    #+#             */
/*   Updated: 2024/02/06 17:20:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_hand_default(int signum)
{
    if (signum == CTRL_C)
    {
        ft_printf("\n");
        rl_replace_line("", 1);
		rl_on_new_line(); // cursor nueva linia
		rl_redisplay(); // redibuja la pantalla de entrada mostrando los cambios echos
    }
}

int	init_signals(int status)
{
    siganl(CTRL_C, signal_hand_default);
    return (1);
}
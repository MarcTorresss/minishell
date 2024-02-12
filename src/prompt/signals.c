/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<<< HEAD:src/expansor/expansor.c
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
========
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
>>>>>>>> lexer:src/prompt/signals.c

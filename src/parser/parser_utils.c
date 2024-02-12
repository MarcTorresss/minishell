/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:26:52 by martorre          #+#    #+#             */
/*   Updated: 2024/02/12 17:00:12 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    lexer_clear(t_lxr *lxr)
{
    t_lxr   *tmp;

    while (lxr != NULL)
    {
        tmp = lxr;
        lxr = lxr->next;
        free(tmp);
    }
}

int	ft_sizelst(t_lxr *list)
{
	int		i;

	i = 0;
	while (list != NULL)
	{
		list = list->next;
		i++;
	}
	return (i);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:26:42 by marvin            #+#    #+#             */
/*   Updated: 2024/02/05 11:26:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t' || c == '\r' || c == '\v'
        || c == '\f' || c == '\n')
        return (1);
    return (0);
}

int ft_isquote(char c)
{
    if (c == QUOTE_ONE || c == QUOTE_TOW)
        return (1);
    return (0);
}

t_lxr   *ft_last_lxr(t_lxr *lxr)
{
    t_lxr   *last;

    if (!lxr)
        return (0);
    last = lxr;
    while (last->next != NULL)
        last = last->next;
    return (last);
}

void    ft_lxr_addback(t_lxr *lxr, t_lxr *new)
{
    t_lxr   *last;

    if (lxr->next != NULL)
    {
        last = ft_last_lxr(lxr);
        last->next = new;
    }
    else
        lxr = new;
}

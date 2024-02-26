/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:26:42 by marvin            #+#    #+#             */
/*   Updated: 2024/02/26 15:12:01 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\r' || c == '\v' || c == '\f'
		|| c == '\n')
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == QUOTE_ONE || c == QUOTE_TOW)
		return (1);
	return (0);
}

int	ft_issign(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	ft_issigntoken(char c)
{
	if (c == PIPE || c == GREAT || c == LESS || c == GREAT_T || c == LESS_T)
		return (1);
	return (0);
}

t_lxr	*ft_last_lxr(t_lxr *lxr)
{
	t_lxr	*last;

	if (!lxr)
		return (0);
	last = lxr;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

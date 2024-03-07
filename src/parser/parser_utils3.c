/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:16:16 by martorre          #+#    #+#             */
/*   Updated: 2024/03/07 11:39:23 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_args(t_lxr *lxr)
{
	t_lxr	*tmp;
	int		i;

	i = 0;
	tmp = lxr;
	while (tmp != NULL && tmp->sign != PIPE)
	{
		if (tmp->sign == NOTH)
			i++;
		if (tmp->sign != NOTH && tmp->next != NULL)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (i);
}

int	check_signs(t_lxr *lxr, int qtt)
{
	t_lxr	*last;

	last = ft_last_lxr(lxr);
	if ((qtt == 0 && ft_issigntoken(lxr->sign) == 1)
		|| ft_issigntoken(last->sign) == 1)
		return (check_error(lxr), -1);
	return (0);
}

int	check_pipes(t_lxr *lxr)
{
	t_lxr	*tmp;

	tmp = lxr;
	while (tmp != NULL)
	{
		if (tmp->sign == PIPE && tmp->next != NULL && tmp->next->sign != NOTH)
			return (ft_fprintf(2, ERROR_TOKEN_NL), -1);
		tmp = tmp->next;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:38:53 by martorre          #+#    #+#             */
/*   Updated: 2024/02/26 17:01:26 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	lexer_clear(t_lxr **lxr)
{
	t_lxr	*tmp;

	while (*lxr != NULL)
	{
		tmp = *lxr;
		*lxr = (*lxr)->next;
		free(tmp->word);
		free(tmp);
	}
}

void	ft_clean_lxr_prs(t_cmd **table, t_lxr **lxr)
{
	lexer_clear(lxr);
	//(void)table;
	parser_clear(table);
}

int	ft_sizelst(t_lxr *list)
{
	int	i;

	i = 0;
	while (list != NULL)
	{
		list = list->next;
		i++;
	}
	return (i);
}

t_rd	*ft_last_rd(t_rd *redir)
{
	t_rd	*last;

	if (!redir)
		return (0);
	last = redir;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

int	check_error(t_lxr *lxr)
{
	if (lxr->sign == PIPE)
		return (ft_fprintf(2, ERROR_TOKEN_P), -1);
	if (lxr->sign != NOTH && lxr->next == NULL)
		return (ft_fprintf(2, ERROR_TOKEN_NL), -1);
	else if (lxr->next != NULL)
	{
		if (lxr->sign != NOTH && lxr->next->sign == GREAT)
			return (ft_fprintf(2, ERROR_TOKEN_G), -1);
		else if (lxr->sign != NOTH && lxr->next->sign == LESS)
			return (ft_fprintf(2, ERROR_TOKEN_L), -1);
		else if (lxr->sign != NOTH && lxr->next->sign == GREAT_T)
			return (ft_fprintf(2, ERROR_TOKEN_GG), -1);
		else if (lxr->sign != NOTH && lxr->next->sign == LESS_T)
			return (ft_fprintf(2, ERROR_TOKEN_LL), -1);
		else if (lxr->next != NULL && lxr->sign != NOTH
			&& lxr->next->sign == PIPE)
			return (ft_fprintf(2, ERROR_TOKEN_P), -1);
		else if (ft_last_lxr(lxr)->sign != NOTH)
			return (ft_fprintf(2, ERROR_TOKEN_NL), -1);
	}
	return (-1);
}

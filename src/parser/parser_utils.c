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

t_prs *init_parser(void)
{
	t_prs *new;

	new = malloc(sizeof(t_prs));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->args = NULL;
	new->type = NULL;
}

t_prs	*ft_last_prs(t_prs *table)
{
	t_prs	*last;

	if (!table)
		return (0);
	last = table;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	ft_prs_addback(t_prs *table, t_prs *new)
{
	t_prs	*last;

	if (table)
	{
		last = ft_last_prs(table);
		last->next = new;
	}
	else
		lst = new;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:38:53 by martorre          #+#    #+#             */
/*   Updated: 2024/02/19 14:54:37 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    lexer_clear(t_lxr **lxr)
{
    t_lxr   *tmp;

    while (*lxr != NULL)
    {
        tmp = *lxr;
        *lxr = (*lxr)->next;
        free(tmp->word);
        free(tmp);
    }
}

void    parser_clear(t_cmd **table)
{
    int     i;
    t_cmd   *tmp;

    while (*table != NULL)
    {
        i = 0;
        tmp = *table;
        while ((*table)->args[i] != NULL)
        {
            free(tmp->args[i]);
            i++;
        }
        *table = (*table)->next;
        free(tmp);
    }
    free((*table)->args);
    table = NULL;
}

void    ft_clean_lxr_prs(t_cmd **table, t_lxr **lxr)
{
    lexer_clear(lxr);
    (void) table;
    //parser_clear(table);
}

char	**free_all(char **mat, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(mat[j]);
		j++;
	}
	free(mat);
	return (NULL);
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

t_rd    *ft_last_rd(t_rd *redir)
{
    t_rd    *last;

    if (!redir)
        return (0);
    last = redir;
    while (last->next != NULL)
        last = last->next;
    return (last);
}
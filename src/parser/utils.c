/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:38:53 by martorre          #+#    #+#             */
/*   Updated: 2024/02/15 15:41:18 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void    lexer_clear(t_lxr *lxr)
{
    t_lxr   *tmp;

    while (lxr != NULL)
    {
        tmp = lxr;
        lxr = (lxr)->next;
        free(tmp->word);
        free(tmp);
    }
}

void    parser_clear(t_cmd *table)
{
    int     i;
    t_cmd   *tmp;

    while (table != NULL)
    {
        i = 0;
        tmp = table;
        while (table->args[i] != NULL)
        {
            free(tmp->args[i]);
            i++;
        }
        table = table->next;
        free(tmp);
    }
    table = NULL;
}

void    ft_clean_lxr_prs(t_cmd *table, t_lxr *lxr)
{
    lexer_clear(lxr);
    parser_clear(table);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:38:53 by martorre          #+#    #+#             */
/*   Updated: 2024/02/15 13:35:25 by martorre         ###   ########.fr       */
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
    t_cmd   *temp;

    i = 0;
    while (table != NULL && table->args[i] != NULL)
    {
        tmp = table;
        free(tmp->args[i]);
        i++;
    }
    while (table != NULL)
    {
        temp = table;
        table = table->next;
        free(tmp);
    }
}

void    ft_clean_lxr_prs(t_cmd *table, t_lxr *lxr)
{
    lexer_clear(lxr);
    parser_clear(table);
}


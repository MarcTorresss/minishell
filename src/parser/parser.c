/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:18:54 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 17:01:54 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define ERROR_TOKEN_P "syntax error near unexpected token '|'"
#define ERROR_TOKEN_L "syntax error near unexpected token '<'"
#define ERROR_TOKEN_G "syntax error near unexpected token '>'"

int count_and_check_comands(t_lxr *lxr)
{
    int qtt_tok;
    int qtt_cmd;

    qtt_tok = ft_sizelst(lxr);
    qtt_cmd = 0;
    while (lxr)
	{
		if (lxr->sign != NOTH)
		{
            if (lxr->next->sign != NOTH || lxr->prev->sign != NOTH)
                return (ft_fprintf(2, ERROR_TOKEN_P), -1);
            else
                qtt_tok++;
		}
	}
    return (qtt_tok);
}

int ft_parser(t_prs *table, t_lxr *lxr)
{
    //t_prs   *new;

    table->qtt_args = count_and_check_comands(lxr);
    if (table->qtt_args == -1)
        return (lexer_clear(lxr), 1);
    /*while (lxr->next != NULL)
    {
        new = init_parser();
        if (!new)
            return (1);
    }*/
    return (0);
}
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

#define ERROR_TOKEN_P "syntax error near unexpected token '|'\n"
#define ERROR_TOKEN_L "syntax error near unexpected token '<'\n"
#define ERROR_TOKEN_G "syntax error near unexpected token '>'\n"
#define ERROR_TOKEN_NL "syntax error near unexpected token\n"

int count_and_check_comands(t_lxr *lxr)
{
	int qtt_cmd;

	qtt_cmd = 0;
	while (lxr)
	{
		if (lxr->sign == PIPE && qtt_cmd == 0)
			return (ft_fprintf(2, ERROR_TOKEN_P), -1);
		else if (lxr->sign == GREAT || lxr->sign == GREAT_T
			|| lxr->sign == LESS || lxr->sign == LESS_T)
		{
			if (lxr->next == NULL)
				return (ft_fprintf(2, ERROR_TOKEN_NL, -1));
			else if (lxr->next->sign != NOTH)
			{
				if (lxr->next->sign == GREAT)
					return (ft_fprintf(2, ERROR_TOKEN_G), -1);
				if (lxr->next->sign == GREAT_T)
					return (ft_fprintf(2, ERROR_TOKEN_G), -1);
				if (lxr->next->sign == LESS)
					return (ft_fprintf(2, ERROR_TOKEN_G), -1);
				if (lxr->next->sign == LESS_T)
					return (ft_fprintf(2, ERROR_TOKEN_G), -1);
				if (lxr->next->sign == PIPE)
					return (ft_fprintf(2, ERROR_TOKEN_G), -1);
			}
		}
		qtt_cmd++;
	}
	return (qtt_cmd++);
}

int	add_command(t_lxr *lxr, t_prs *new)
{
	t_lxr	*tmp;
	int		i;

	i = 0;
	tmp = lxr;
	while (tmp->sign != PIPE)
	{
		if (tmp->sign != NONE)
			ft_isredir(new);
		else
		{
			new->args[i] = ft_strdup(tmp->word);
			if (!new->args[i])
				return (free_all(new, i), -1);
		}
		tmp = tmp->next;
		i++;
	}
}

int	create_command(t_lxr *lxr, t_prs *new, int qtt_args)
{
	new->args = malloc(sizeof(char *) * (qtt_args + 1));
	if (!new->args)
		return (-1);
	new->args[qtt_args] = NULL;
	if (add_command(lxr, new) == -1)
		return (-1);
}

int ft_parser(t_prs *table, t_lxr *lxr)
{
    t_prs   *new;
	int		qtt_args;

    qtt_args = count_and_check_comands(lxr);
    if (qtt_args == -1)
        return (lexer_clear(lxr), 1);
    while (lxr->next != NULL)
    {
        new = init_parser();
        if (!new)
            return (1);
		ft_prs_addback(table, new);
		create_command(lxr, new, qtt_args);
    }
    return (0);
}
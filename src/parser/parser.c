/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:18:54 by marvin            #+#    #+#             */
/*   Updated: 2024/02/15 15:55:37 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int check_error(int sign)
{
	if (sign == GREAT)
		return (ft_fprintf(2, ERROR_TOKEN_G), -1);
	if (sign == GREAT_T)
		return (ft_fprintf(2, ERROR_TOKEN_GG), -1);
	if (sign == LESS)
		return (ft_fprintf(2, ERROR_TOKEN_L), -1);
	if (sign == LESS_T)
		return (ft_fprintf(2, ERROR_TOKEN_LL), -1);
	if (sign == PIPE)
		return (ft_fprintf(2, ERROR_TOKEN_P), -1);
    return (0);    
}

int count_and_check_comands(t_lxr *lxr)
{
	int     qtt_cmd;
    t_lxr   *tmp;

	qtt_cmd = 0;
    tmp = lxr;
	while (tmp)
	{
		if (tmp->sign == PIPE && qtt_cmd == 0)
			return (ft_fprintf(2, ERROR_TOKEN_P), -1);
		else if (tmp->sign == GREAT || tmp->sign == GREAT_T
			|| tmp->sign == LESS || tmp->sign == LESS_T)
		{
			if (tmp->next == NULL)
				return (ft_fprintf(2, ERROR_TOKEN_NL, -1));
			else if (tmp->next->sign != NOTH)
                return (check_error(tmp->next->sign));
		}
		if (tmp->sign != PIPE)
			qtt_cmd++;
        tmp = tmp->next;
	}
	return (qtt_cmd);
}

int	ft_isredir(t_lxr **lxr, t_rd **redir)
{
	t_rd	*new;

	new = init_redir();
	if (!new)
		return (-1);
	ft_addback_redir(new, redir);
    if (lxr->sign == GREAT)
        new->type = OUTPUT_REDIR;
	else if (lxr->sign == GREAT_T)
		new->type = APPEND_TO_END;
	else if (lxr->sign == LESS)
		new->type = INPUT_REDIR;
	else if (lxr->sign == LESS_T)
		new->type = HEREDOC;
	new->file = ft_strdup(lxr->next->word);
	if (!new->file)
		return (-1);
	(*lxr) = (*lxr)->next;
	return (0);
}

int	add_command(t_lxr **lxr, t_cmd *new, t_rd **redir)
{
	int	i;

	i = 0;
	while ((*lxr) != NULL && (*lxr)->sign != PIPE)
	{
		if ((*lxr)->sign != NOTH)
			if (ft_isredir(*lxr, redir) == -1)
				return (-1);
		else
		{
			new->args[i] = ft_strdup((*lxr)->word);
			if (!new->args[i])
				return (free_all(new->args, i), -1);	
			//printf("\nword = %s\n", new->args[i]);
		}
		(*lxr) = (*lxr)->next;
		i++;
	}
	new->redir = *redir;
    return (0);
}

int	create_command(t_lxr **lxr, t_cmd **new, int qtt_args)
{
	t_rd	*redir;

	redir = NULL;
	(*new)->args = malloc(sizeof(char *) * (qtt_args + 1));
	if (!(*new)->args)
		return (-1);
	(*new)->args[qtt_args] = NULL;
	if (add_command(lxr, *new, &redir) == -1)
		return (-1);
    return (0);
}

int ft_parser(t_cmd **table, t_lxr **lxr)
{
    t_cmd   *new;
    t_lxr   *tmp;
	int		qtt_args;

    tmp = *lxr;
    qtt_args = count_and_check_comands(*lxr);
    if (qtt_args == -1)
        return (lexer_clear(*lxr), -1);
    while (tmp != NULL)
    {
        new = init_parser();
        if (!new)
            return (-1);
		ft_cmd_addback(table, new);
		if (create_command(&tmp, &new, qtt_args) == -1)
			return (-1);
		if (tmp != NULL)
        	tmp = tmp->next;
    }
    return (0);
}

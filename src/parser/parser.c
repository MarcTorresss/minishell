/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:18:54 by marvin            #+#    #+#             */
/*   Updated: 2024/02/22 12:28:04 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_signs(t_lxr *lxr, int qtt)
{
	t_lxr	*last;

	last = ft_last_lxr(lxr);
	if ((qtt == 0 && ft_issigntoken(lxr->sign) == 1)
			|| ft_issigntoken(last->sign) == 1)
		return (check_error(lxr), -1);
	return (0);
}
int check_comands(t_lxr *lxr)
{
    t_lxr   *tmp;
	int		qtt;

    tmp = lxr;
	qtt = 0;
	while (tmp)
	{
		if (check_signs(lxr, qtt) == -1)
			return (-1);
		else if (tmp->sign == GREAT || tmp->sign == GREAT_T
			|| tmp->sign == LESS || tmp->sign == LESS_T)
		{
			if (tmp->next == NULL)
				return (ft_fprintf(2, ERROR_TOKEN_NL, -1));
			else if (tmp->next->sign != NOTH)
                return (check_error(tmp->next));
		}
		if (tmp->sign == PIPE)
			qtt++;
		tmp = tmp->next;
	}
	return (0);
}

int	ft_isredir(t_lxr **lxr, t_rd **redir)
{
	t_rd	*new;

	new = init_redir();
	if (!new)
		return (-1);
    if ((*lxr)->sign == GREAT)
        new->type = OUTPUT_REDIR;
	else if ((*lxr)->sign == GREAT_T)
		new->type = APPEND_TO_END;
	else if ((*lxr)->sign == LESS)
		new->type = INPUT_REDIR;
	else if ((*lxr)->sign == LESS_T)
		new->type = HEREDOC;
	new->file = ft_strdup((*lxr)->next->word);
	if (!new->file)
		return (-1);
	ft_addback_redir(redir, new);
	(*lxr) = (*lxr)->next;
	return (0);
}

int	add_command(t_lxr **lxr, t_cmd *new, t_rd **redir)
{
	int	i;

	i = 0;
	while ((*lxr) != NULL)
	{
		if ((*lxr)->sign == PIPE)
			(*lxr) = (*lxr)->next;
		if ((*lxr)->sign != NOTH)
		{
			if (ft_isredir(lxr, redir) == -1)
				return (-1);
		}
		else
		{
			new->args[i] = ft_strdup((*lxr)->word);
			if (!new->args[i])
				return (free_all(new->args, i), -1);	
			i++;
		}
		(*lxr) = (*lxr)->next;
	}
	
	new->redir = *redir;
    return (0);
}

int	create_command(t_lxr **lxr, t_cmd **new, int qtt_args)
{
	t_rd	*redir;

	redir = NULL;
	if ((*lxr)->sign == NOTH)
	{
		(*new)->args = malloc(sizeof(char *) * (qtt_args + 1));
		if (!(*new)->args)
			return (-1);
		(*new)->args[qtt_args] = NULL;
	}
	if (add_command(lxr, *new, &redir) == -1)
		return (-1);
    return (0);
}

int	count_args(t_lxr *lxr)
{
	t_lxr	*tmp;
	int	i;

	tmp = lxr;
	i = 0;

	while (tmp != NULL)
	{
		if (tmp->sign == NOTH)
			i++;
		if (tmp->sign != NOTH && tmp->sign != PIPE && tmp->next != NULL)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	return (i);
}

int ft_parser(t_cmd **table, t_lxr **lxr)
{
    t_cmd   *new;
    t_lxr   *tmp;
	int		qtt_args;
	int		check;

    tmp = *lxr;
	qtt_args = count_args(tmp);
	printf("qtt_args = %d\n", qtt_args);
    while (tmp != NULL)
    {
    	check = check_comands(*lxr);
		if (check == -1)
			return (lexer_clear(lxr), -1);
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

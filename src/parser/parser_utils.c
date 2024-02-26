/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:26:52 by martorre          #+#    #+#             */
/*   Updated: 2024/02/26 15:18:39 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmd	*init_parser(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->args = NULL;
	new->redir = NULL;
	return (new);
}

t_cmd	*ft_last_cmd(t_cmd *table)
{
	t_cmd	*last;

	if (!table)
		return (0);
	last = table;
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	ft_cmd_addback(t_cmd **table, t_cmd *new)
{
	t_cmd	*last;

	if (*table != NULL)
	{
		last = ft_last_cmd(*table);
		last->next = new;
	}
	else
		*table = new;
}

t_rd	*init_redir(void)
{
	t_rd	*new;

	new = malloc(sizeof(t_rd));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->file = NULL;
	new->type = 10;
	return (new);
}

void	ft_addback_redir(t_rd **redir, t_rd *new)
{
	t_rd	*last;

	if (*redir != NULL)
	{
		last = ft_last_rd(*redir);
		last->next = new;
	}
	else
		*redir = new;
}

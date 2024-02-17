/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:26:52 by martorre          #+#    #+#             */
/*   Updated: 2024/02/15 12:42:52 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

t_cmd	*init_parser(void)
{
	t_cmd *new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->args = NULL;
	new->type = NOTHING;
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
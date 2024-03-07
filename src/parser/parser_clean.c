/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:56:21 by martorre          #+#    #+#             */
/*   Updated: 2024/03/07 13:29:22 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void	ft_redir_clear(t_rd **redir)
{
	t_rd	*tmp;
	t_rd	*tmp2;

	tmp = *redir;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp->file);
		free(tmp);
		tmp = tmp2;
	}
	*redir = NULL;
}

int	ft_len_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

void	parser_clear(t_cmd **table)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;

	tmp = *table;
	while (tmp)
	{
		tmp2 = tmp->next;
		free_all(tmp->args, ft_len_array(tmp->args));
		ft_redir_clear(&tmp->redir);
		free(tmp);
		tmp = tmp2;
	}
	*table = NULL;
}

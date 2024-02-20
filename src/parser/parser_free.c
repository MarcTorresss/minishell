/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:16:16 by martorre          #+#    #+#             */
/*   Updated: 2024/02/20 11:11:06 by martorre         ###   ########.fr       */
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
void    parser_clear(t_cmd **table)
{
    int     i;
    t_cmd   *tmp;

    while (*table != NULL)
    {
        tmp = *table;
        i = 0;
        while ((*table)->args && (*table)->args[i] != NULL)
        {
            free(tmp->args[i]);
            i++;
        }
        free((*table)->args);
        *table = (*table)->next;
        free(tmp);
    }
    *table = NULL;
}

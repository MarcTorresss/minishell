/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:11:39 by martorre          #+#    #+#             */
/*   Updated: 2024/03/13 15:45:45 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_lxr	*init_lxr(void)
{
	t_lxr	*new;

	new = malloc(sizeof(t_lxr));
	if (!new)
		return (NULL);
	new->word = NULL;
	new->next = NULL;
	new->sign = NOTH;
	return (new);
}

t_lxr	*ft_lxr_addback(t_lxr *lxr, t_lxr *new)
{
	t_lxr	*last;

	if (lxr != NULL)
	{
		last = ft_last_lxr(lxr);
		last->next = new;
	}
	else
		lxr = new;
	return (lxr);
}

void	change_val(char *str, int i, int *isquote, int *isquoteTwo)
{
	if (str[i] == QUOTE_ONE)
		*isquote = 0;
	else if (str[i] == QUOTE_TOW)
		*isquoteTwo = 0;
}

int	init_word(char *str)
{
	int	i;
	int	isquote;
	int	isquoteTwo;

	i = 0;
	isquote = 0;
	isquoteTwo = 0;
	while (str[i] != '\0')
	{
		if (ft_isquote(str[i]) == 1 && (isquote == 1 || isquoteTwo == 1))
			change_val(str, i, &isquote, &isquoteTwo);
		else if (ft_isquote(str[i]) == 1 && (isquote == 0 || isquoteTwo == 0))
		{
			if (str[i] == QUOTE_ONE)
				isquote = 1;
			else if (str[i] == QUOTE_TOW)
				isquoteTwo = 1;
		}
		if ((ft_isspace(str[i]) == 1 || ft_issign(str[i]) == 1) && (isquote == 0 && isquoteTwo == 0))
			break ;
		i++;
	}
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:11:39 by martorre          #+#    #+#             */
/*   Updated: 2024/03/13 12:02:20 by martorre         ###   ########.fr       */
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

void	change_val(char *str, int *i, int *isquoteOne, int *isquoteTwo)
{
	if (str[*i] == QUOTE_ONE)
		*isquoteOne += 1;
	else if (str[*i] == QUOTE_TOW)
		*isquoteTwo += 1;
	(*i)++;
	if (str[*i] == QUOTE_ONE)
		*isquoteOne += 1;
	else if (str[*i] == QUOTE_TOW)
		*isquoteTwo += 1;
}

int	init_word(char *str)
{
	int	i;
	int	isquoteOne;
	int	isquoteTwo;

	i = 0;
	isquoteOne = 0;
	isquoteTwo = 0;
	while (str[i] != '\0')
	{
		if (ft_isquote(str[i]) == 1 && (isquoteOne == 0 || isquoteTwo == 0) && str[i + 1] != '\0')
			change_val(str, &i, &isquoteOne, &isquoteTwo);
		if (ft_isquote(str[i]) == 1 && ((isquoteOne % 2 == 0) || (isquoteTwo % 2 == 0)) && ft_isspace(str[i + 1]) == 1)
			break ;
		if ((ft_isspace(str[i]) == 1 || ft_issign(str[i]) == 1) && ((isquoteOne % 2 == 0) && (isquoteTwo % 2 == 0)))
			return (i);
		i++;
	}
	i++;
	return (i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:11:39 by martorre          #+#    #+#             *//*                                                                            */
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

int	init_word(char *str)
{
	int	i;
	int	isquote;

	i = 0;
	isquote = 0;
	while (str[i] != '\0')
	{
    if (ft_isquote(str[i]) == 1 && isquote == 0 && str[i + 1] != '\0')
		{
			isquote = 1;
			i++;
		}
		if ((ft_isspace(str[i]) == 1 || ft_issign(str[i]) == 1) && isquote == 0)
			return (i);
		else if ((ft_isquote(str[i]) == 1) && isquote == 1)
			break ;
		i++;
	}
	i++;
	return (i);
}

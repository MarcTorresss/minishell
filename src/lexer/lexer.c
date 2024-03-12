/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:07:06 by martorre          #+#    #+#             */
/*   Updated: 2024/03/12 12:58:26 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_sign(char *str, t_lxr *new)
{
	int	i;

	i = 0;
	if (str[i] == PIPE_AC)
		new->sign = PIPE;
	else if (str[i] == GREAT_AC && str[i + 1] == GREAT_AC)
		new->sign = GREAT_T;
	else if (str[i] == LESS_AC && str[i + 1] == LESS_AC)
		new->sign = LESS_T;
	else if (str[i] == GREAT_AC && str[i + 1] != GREAT_AC)
		new->sign = GREAT;
	else if (str[i] == LESS_AC && str[i + 1] != LESS_AC)
		new->sign = LESS;
	if (new->sign == LESS_T || new->sign == GREAT_T)
		i = 2;
	else
		i = 1;
	return (i);
}

int	ft_convert(char *str, t_lxr *new)
{
	int	i;

	i = 0;
	if (ft_issign(str[i]) == 1)
		i = init_sign(str, new);
	else
	{
		i = init_word(str);
		new->word = ft_substr(str, 0, i);
		if (!new->word)
			return (free(str), -1);
	}
	free(str);
	return (i - 1);
}

int	ft_scape_space(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (-1);
	add_history(str);
	return (0);
}

int	ft_lexer(char *str, t_lxr **lxr)
{
	t_lxr	*new;
	int		i;
	int		check;

	i = 0;
	if (ft_scape_space(str, i) == -1)
		return (1);
	while (i < ft_strlen(str))
	{
		if (ft_isspace(str[i]) == 1)
			i++;
		else
		{
			new = init_lxr();
			if (!new)
				return (1);
			*lxr = ft_lxr_addback(*lxr, new);
			check = ft_convert(ft_substr(str, i, ft_strlen(str)), new);
			if (check == -1)
				return (1);
			i += check;
			i++;
		}
	}
	return (0);
}

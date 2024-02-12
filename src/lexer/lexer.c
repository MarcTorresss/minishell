/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:07:06 by martorre          #+#    #+#             */
/*   Updated: 2024/02/12 15:51:03 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	init_word(char *str)
{
	int	i;
	int	isquote;

	i = 0;
	isquote = 0;
	while  (str[i] != '\0')
	{
		if (ft_isspace(str[i]) == 1 || ft_issign(str[i] == 1))
			return	(i); 
		if (ft_isquote(str[i]) == 1 && isquote == 0)
		{
			isquote = 1;
			i++;
		}
		else if ((ft_isquote(str[i] == 1) && isquote == 1))
			break ;
		i++;
	}
	return (i);
}

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
	int		i;

	i = 0;
	if (ft_issign(str[i]) == 1)
		i = init_sign(str, new);
	else
	{
		printf("\n%i\n", i);
		i = init_word(str);
		new->word = ft_substr(str, 0, i);
		if (!new->word)
			return (-1);
	}
	return (i);
}

t_lxr	*init_lxr(void)
{
	t_lxr	*new;

	new = malloc(sizeof(t_lxr));
	if (!new)
		return (NULL);
	new->word = NULL;
	new->next = NULL;
	new->sign = NOTH;
	new->prev = NULL;
	return (new);
}

void	print_lex(t_lxr *lxr)
{
	ft_fprintf(1, "\nStack Lxr\n");
	while (lxr != NULL)
	{
		ft_fprintf(1, "\nword = %s -> sig = %d\n", lxr->word, lxr->sign);
		lxr = lxr->next;
	}

}

int	ft_lexer(char *str, t_lxr *lxr)
{
	t_lxr	*new;
	size_t	i;
	int		check;

	i = 0;
	while (i <= ft_strlen(str))
	{
		if (ft_isspace(str[i]) == 1)
			i++;
		else
		{
			new = init_lxr();
			if (!new)
				return (1);
			lxr = ft_lxr_addback(lxr, new);
			check = ft_convert(ft_substr(str, i, ft_strlen(str)), new);
			if (check != -1)  
				i += check;
			else
				return (1);
			//printf("\n%zu\n", i);
			i++;
		}
	}
	//print_lex(lxr);
	return (0);
}
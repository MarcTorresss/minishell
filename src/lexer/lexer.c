/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:07:06 by martorre          #+#    #+#             */
/*   Updated: 2024/02/01 15:18:13 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_word(char *str)
{
	int	i;
	int	isquote;

	i = 0;
	isquote = 0;
	while  (str[i] != '\0')
	{
		if (ft_isquote(str[i]) == 1 && isquote == 0)
		{
			isquote == 1;
			i++;
		}
		else if (ft_isquote(str[i] == 1) && isquote == 1)
			break ;
		i++;
	}
	return (i);
}

int	init_sign(char *str, t_lxr *new)
{
	int	i;

	i = 0,
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
		lxr->word = ft_substr(str, 0, i);
		if (!lxr->word)
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
	return (new);
}

int	str_to_list(char *str, t_lxr *lxr)
{
	t_lxr	*new;
	int		i;
	int		check;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]) == 1)
			i++;
		else
		{
			new = init_lxr();
			if (!new)
				return (1);
			ft_lxr_addback(lxr, new);
			check = ft_convert(ft_substr(str, i, ft_strlen(str)), new);
			if (check != -1)  
				i += check;
			else
				return (1);
		}
	}
	return (0);
}

/*int main()
{
	t_lxr   *new;
    str_to_list("ls >> aaaa < cat", new);
	ft_printf("\nStack Lxr\n");
	while (new != NULL)
	{
		ft_printf("%s\n", new->word);
		new = new->next;
	}
}*/
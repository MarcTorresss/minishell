/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:47:32 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/14 14:47:25 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_name(char *input)
{
	int		i;
	char	space_f;

	i = 0;
	space_f = 0;
	while (input[i] && input[i] != '=')
	{
		if (input[i] == ' ' && space_f)
			break ;
		if (input[i] != ' ')
			space_f = 1;
		i++;
	}
	return (ft_substr(input, 1, i - 1));
}

char	*get_value(char *input)
{
	int	i;
	int	j;
	int	found_f;

	i = 0;
	found_f = 0;
	while (input[i])
	{
		if (input[i] == '=')
		{
			found_f = 1;
			break ;
		}
		i++;
	}
	if (!found_f)
		return (NULL);
	j = i;
	if (!input[j])
		return (ft_strdup(""));
	while (input[j] && input[j] != ' ')
		j++;
	return (ft_substr(input, i + 1, j - i));
}

int	update_value(char *name, char *value, t_env **exp)
{
	t_env	*tmp;
	int		exists_f;

	tmp = *exp;
	exists_f = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			if (value)
				tmp->value = value;
			exists_f = 1;
		}
		tmp = tmp->next;
	}
	return (exists_f);
}

int forbidden_char(char *input)
{
	int i = 0;
	if (ft_isdigit(input[i]))
		return 1;
	while (input[i])
	{
		if (input[i] == '=')
			return 0;
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return 1;
		i++;
	}
	return 0;
}

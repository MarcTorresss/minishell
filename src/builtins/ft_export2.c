/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 16:47:32 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/15 18:03:39 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_name(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '=')
			break ;
		i++;
	}
	return (ft_substr(input, 1, i - 1));
}

char	*get_value(char *input)
{
	int	i;
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
	return (ft_substr(input, i + 1, ft_strlen(input)));
}

int	update_value(char *name, char *value, t_env **exp, int append)
{
	t_env	*tmp;
	int		exists_f;

	tmp = *exp;
	exists_f = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			if (value && append)
				tmp->value = ft_join_n_destroy(tmp->value, value, 3);
			else
				tmp->value = value;
			exists_f = 1;
			break ;
		}
		tmp = tmp->next;
	}
	return (exists_f);
}

int forbidden_char(char *input)
{
	int	i;

	i = 0;
	if (ft_isdigit(input[i]))
		return (1);
	while (input[i])
	{
		if (input[i] == '=')
			return (0);
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

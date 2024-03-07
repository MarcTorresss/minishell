/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:20:47 by rbarbier          #+#    #+#             */
/*   Updated: 2024/03/07 11:13:29 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*find_env(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	swap_data(t_env *nod1, t_env *nod2)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = nod1->name;
	temp_value = nod1->value;
	nod1->name = nod2->name;
	nod1->value = nod2->value;
	nod2->name = temp_name;
	nod2->value = temp_value;
}

int	forbidden_char(char *input)
{
	int	i;

	i = 0;
	if (input == NULL)
		return (0);
	if (ft_isdigit(input[i]))
		return (1);
	while (input[i])
	{
		if ((input[i] == '=' || (input[i] == '+' && input[i + 1] == '='))
			&& i != 0)
			return (0);
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

char	*get_name(char *input)
{
	int	i;

	i = 0;
	if (input == NULL)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '=' || (input[i] == '+' && input[i + 1] == '='))
			break ;
		i++;
	}
	return (ft_substr(input, 0, i));
}

char	*get_value(char *input)
{
	int	i;
	int	found_f;

	i = 0;
	found_f = 0;
	if (input == NULL)
		return (NULL);
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

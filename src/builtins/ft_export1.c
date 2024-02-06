/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:01:29 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/06 16:48:40 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	swap_data(t_env *nod1, t_env *nod2)
{
    char *temp_name;
    char *temp_value;

	temp_name = nod1->name;
	temp_value = nod1->value;
    nod1->name = nod2->name;
    nod1->value = nod2->value;
    nod2->name = temp_name;
    nod2->value = temp_value;
}

void	 sort_export(t_env **exp)
{
	t_env	*node;
	t_env	*start;
	int		sorted_f;
	
	node = *exp;
	start = *exp;
	sorted_f = 1;
	while (sorted_f)
	{
		sorted_f = 0;
		while (node->next)
		{
			if (ft_strncmp(node->name, node->next->name, ft_strlen(node->name) + 1) > 0)
			{
				swap_data(node, node->next);
				sorted_f = 1;
			}
			node = node->next;
		}
		node = start;
	}
}

void	export_print(t_env **exp)
{
	t_env	*tmp;

	tmp = *exp;
	while (tmp)
	{
		ft_printf("declare -x %s", tmp->name);
		if (tmp->value)
			ft_printf("=\"%s\"\n", tmp->value);
		else
			ft_printf("\n");
		tmp = tmp->next;
	}
}

void	ft_export(t_env **exp, t_env **env, char *input)
{
	char	*name;
	char	*value;

	value = NULL;
	if (!ft_strlen(input))
	{	
		sort_export(exp);
		export_print(exp);
	}
	else
	{
		name = get_name(input);
		value = get_value(input);
		if (!update_value(name, value, exp))
			new_env_var(name, value, exp);
		if (!update_value(name, value, env))
			if (value)
				new_env_var(name, value, env);
	}
	g_exit = 0;
}

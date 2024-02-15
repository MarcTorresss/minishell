/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:01:29 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/15 17:44:53 by rbarbier         ###   ########.fr       */
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

void	export_print(t_env **exp)
{
	t_env	*tmp;

	tmp = *exp;
	while (tmp)
	{
		ft_fprintf(1, "declare -x %s", tmp->name);
		if (tmp->value)
			ft_fprintf(1 ,"=\"%s\"\n", tmp->value);
		else
			ft_fprintf(1 ,"\n");
		tmp = tmp->next;
	}
}

void	 sort_export(t_env **exp)
{
	t_env	*node;
	t_env	*start;
	int		sorted_f;

	node = *exp;
	start = *exp;
	sorted_f = 1;
	if (!node)
		return ;
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
	export_print(exp);
}

void	export_process(t_env **exp, t_env **env, char *cmd)
{
	char	*name;
	char	*value;

	value = NULL;
	if (forbidden_char(cmd))
	{
		ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n", cmd);
		exit_value(1);
	}
	else
	{
		name = get_name(cmd);
		value = get_value(cmd);
		if (!update_value(name, value, exp))
			new_env_var(name, value, exp);
		if (!update_value(name, value, env) && value)
			new_env_var(name, value, env);
		free(name);
		free(value);
		exit_value(0);
	}
}

void	ft_export(t_env **exp, t_env **env, char **cmd)
{
	int		i;

	i = 0;
	if (!cmd[1])
	{
		sort_export(exp);
		exit_value(0);
	}
	while (cmd[++i])
		export_process(exp, env, cmd[i]);
}

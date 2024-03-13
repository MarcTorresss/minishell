/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 13:01:29 by rbarbier          #+#    #+#             */
/*   Updated: 2024/03/12 14:19:19 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sort_export(t_env **exp)
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
			if (ft_strncmp(node->name, node->next->name, ft_strlen(node->name)
					+ 1) > 0)
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

void	update_value2(t_env *tmp, char *value, int append)
{
	if (append)
		tmp->value = ft_join_n_destroy(tmp->value, value, 1);
	else if (value && tmp->value)
	{
		free(tmp->value);
		tmp->value = ft_strdup(value);
	}
	else if (value)
		tmp->value = ft_strdup(value);
}

int	update_value(char *name, char *value, t_env **exp, int append)
{
	t_env	*tmp;
	int		exists_f;

	tmp = *exp;
	exists_f = 0;
	if (!name)
		return (0);
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			update_value2(tmp, value, append);
			exists_f = 1;
			break ;
		}
		tmp = tmp->next;
	}
	return (exists_f);
}

void	export_process(t_env **exp, t_env **env, char *cmd)
{
	char	*name;
	char	*value;
	int		append;

	value = NULL;
	append = 0;
	if (forbidden_char(cmd))
		return (msg_return("export", cmd, "n val id", 1), (void)0);
	name = get_name(cmd);
	value = get_value(cmd);
	if (ft_strncmp(cmd + ft_strlen(name), "+=", 2) == 0)
		append = 1;
	if (!update_value(name, value, exp, append))
		new_env_var(name, value, exp);
	if (!update_value(name, value, env, append) && value)
		new_env_var(name, value, env);
	if (value)
		free(value);
	if (name)
		free(name);
}

void	ft_export(t_env **exp, t_env **env, char **cmd)
{
	int	i;

	i = 0;
	if (!cmd[1] || !cmd[1][0])
		sort_export(exp);
	else
	{
		exit_status(0);
		while (cmd[++i])
			export_process(exp, env, cmd[i]);
	}
}

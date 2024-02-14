/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:08:37 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/14 11:00:35 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_var(char *str, int *i, t_env **env)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;

	if (str[*i] == '?')
	{
		var_name = ft_strdup("?");
		var_value = ft_itoa(exit_value(0));
	}
	else
	{
		var_name = get_var_name(str, *i + 1);
		var_value = (find_env(env, var_name))->value;
	}
	tmp = ft_join_n_destroy(ft_substr(str, 0, *i), var_value, 1);
	tmp = ft_join_n_destroy(tmp, ft_substr(str, *i + ft_strlen(var_name) + 1, \
			ft_strlen(str) - *i - ft_strlen(var_name) - 1), 3);
	*i = *i + ft_strlen(var_value);
	free(str);
	free(var_name);
	return (tmp);
}

void	expansor(t_prs *cmd, t_env **env, int i, int j)
{
	int		single_f;
	int		double_f;

	single_f = 0;
	double_f = 0;
	while (cmd->args[j])
	{
		while (cmd->args[j][i])
		{
			single_f = single_quote_dealer(cmd->args[j], i, single_f, double_f);
			double_f = double_quote_dealer(cmd->args[j], i, single_f, double_f);
			if ((cmd->args[j][i] == '\'' && single_f) || (cmd->args[j][i] == '\"' && double_f))
			{
				remove_char_at(cmd->args[j], i);
				continue ;
			}
			if (cmd->args[j][i] == '$' && !single_f && (ft_isalnum(cmd->args[j][i + 1]) || cmd->args[j][i + 1] == '_' || cmd->args[j][i + 1] == '?'))
				cmd->args[j] = expand_var(cmd->args[j], &i, env);
			i++;
		}
		i = 0;
		j++;
	}
}

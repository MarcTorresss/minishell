/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:08:37 by rbarbier          #+#    #+#             */
/*   Updated: 2024/03/05 13:27:09 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_var(char *str, int *i, t_env **env)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;
	t_env	*tmp_env;
	if (str[*i + 1] == '?')
		question_mark(&var_name, &var_value);
	else

	{
		var_name = get_var_name(str, *i + 1);
		tmp_env = find_env(env, var_name);
		if (!tmp_env)
			var_value = ft_strdup("");
		else
			var_value = ft_strdup(tmp_env->value);
	}
	tmp = ft_join_n_destroy(ft_substr(str, 0, *i), var_value, 1);
	tmp = ft_join_n_destroy(tmp, ft_substr(str, *i + ft_strlen(var_name) + 1,
				ft_strlen(str)), 3);
	if (ft_strlen(var_value) == 0)
		*i += 1;
	*i = *i + ft_strlen(var_value) - 1;
	free(str);
	free(var_name);
	free(var_value);
	return (tmp);
}

char	*handle_quotes(char *str, int i, int *single_f, int *double_f)
{
	if (!str[i])
		return (str);
	*single_f = single_quote_dealer(str, i, *single_f, *double_f);
	*double_f = double_quote_dealer(str, i, *single_f, *double_f);
	if ((str[i] == '\'' && *single_f) || (str[i] == '\"' && *double_f) \
	|| (!*double_f && !*single_f && (str[i] == '\'' || str[i] == '\"')))
		return (remove_char_at(str, i));
	return (str);
}

char	*handle_dollar_sign(char *str, t_env **env, int *i, int single_f)
{
	if (!str[*i] || !str[*i + 1])
		return (str);
	if (str[*i] == '$' && !single_f && !ft_isdigit(str[*i + 1]) \
	&& (ft_isalnum(str[*i + 1]) || str[*i + 1] == '_' || str[*i + 1] == '?'))
		return (expand_var(str, i, env));
	return (str);
}

int	expand(char **str, int j, t_env **env)
{
	int	single_f;
	int	double_f;
	int	i;

	single_f = 0;
	double_f = 0;
	i = 0;
	// while (str[i])
	// 	printf("%c", str[i++]);
	while (str[j][i])
	{
		str[j] = handle_quotes(str[j], i, &single_f, &double_f);
		str[j] = handle_dollar_sign(str[j], env, &i, single_f);
		if (!str[j][i])
			break ;
		i++;
	}
	if (single_f || double_f)
		return (msg_return(0, 0, "quote not closed", 1), 1);
	else
		return (0);
}

int	expansor(t_cmd *cmd, t_env **env)
{
	int	i;

	i = 0;
	while (cmd)
	{
		while (cmd->args[i])
			if (expand(cmd->args, i++, env))
				return (1);
		// while (cmd->redir)
		// {
		// 	expand(cmd->redir->file, env);
		// 	cmd->redir = cmd->redir->next;
		// }
		cmd = cmd->next;
	}
	return (0);
}

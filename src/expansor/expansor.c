/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:08:37 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/20 15:04:23 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	question_mark(char **var_name, char **var_value)
{
	*var_name = ft_strdup("?");
	*var_value = ft_itoa(exit_status(0));
}

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
	tmp = ft_join_n_destroy(tmp, ft_substr(str, *i + ft_strlen(var_name) + 1, ft_strlen(str)), 3);
	if (*i == 0 && var_value[0] == '\0')
		*i += 1;
	*i = *i + ft_strlen(var_value) - 1;
	free(str);
	free(var_name);
	free(var_value);
	return (tmp);
}

int	handle_quotes(t_cmd *cmd, t_expansion *exp)
{
    exp->single_f = single_quote_dealer(cmd->args[exp->j], exp->i, exp->single_f, exp->double_f);
    exp->double_f = double_quote_dealer(cmd->args[exp->j], exp->i, exp->single_f, exp->double_f);
    if ((cmd->args[exp->j][exp->i] == '\'' && exp->single_f) || (cmd->args[exp->j][exp->i] == '\"' && exp->double_f) || \
            (!exp->double_f && !exp->single_f && (cmd->args[exp->j][exp->i] == '\'' || cmd->args[exp->j][exp->i] == '\"')))
	{
        cmd->args[exp->j] = remove_char_at(cmd->args[exp->j], exp->i);
		return (1);
	}
	return (0);
}

int	handle_dollar_sign(t_cmd *cmd, t_env **env, t_expansion *exp)
{
    if (cmd->args[exp->j][exp->i] == '$' && !exp->single_f && !ft_isdigit(cmd->args[exp->j][exp->i + 1]) && \
	(ft_isalnum(cmd->args[exp->j][exp->i + 1]) || cmd->args[exp->j][exp->i + 1] == '_' || cmd->args[exp->j][exp->i + 1] == '?'))
	{
        cmd->args[exp->j] = expand_var(cmd->args[exp->j], &exp->i, env);
		return (1);
	}
	return (0);
}

void	expansor(t_cmd *cmd, t_env **env)
{
    t_expansion exp;

    exp.j = 0;
    while (cmd->args[exp.j])
    {
        exp.i = 0;
        exp.single_f = 0;
        exp.double_f = 0;
        while (cmd->args[exp.j][exp.i])
        {
			if (handle_quotes(cmd, &exp) || handle_dollar_sign(cmd, env, &exp))
			{
				if (cmd->args[exp.j][exp.i] == '\0' || cmd->args == NULL)
					break ;
				continue ;
			}
			exp.i++;
        }
        if (exp.single_f || exp.double_f)
			return (msg_return("unclosed quotes\n", 0, 1));
        exp.j++;
    }
}

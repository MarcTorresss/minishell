/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:08:37 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/12 17:01:13 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	single_quote_dealer(char *str, int i, int single_f, int double_f)
{
	if (!double_f)
	{
		if (str[i] == '\'' && single_f)
			single_f = 0;
		else if (str[i] == '\'' && !single_f)
			single_f = 1;	
	}
	return (single_f);
}

int	double_quote_dealer(char *str, int i, int single_f, int double_f)
{
	if (!single_f)
	{
		if (str[i] == '\"' && double_f)
			double_f = 0;
		else if (str[i] == '\"' && !double_f)
			double_f = 1;	
	}
	return (double_f);
}
char	*get_var_name(char *str, int i)
{
	int		j;
	char	*var_name;

	j = 0;
	while (str[i + j] && (ft_isalnum(str[i + j]) || str[i + j] == '_'))
		j++;
	var_name = ft_substr(str, i, j);
	return (var_name);
}

char	*expand_var(char *str, int *i, t_env **env)
{
	char	*var_name;
	char	*var_value;
	char	*tmp;
	char	*tmp2;

	var_name = get_var_name(str, *i + 1);
	if (var_name == NULL)
		return (NULL);
	var_value = find_env(env, var_name)->value;
	tmp = ft_strjoin(ft_substr(str, 0, *i), var_value);
	tmp2 = ft_strjoin(tmp, ft_substr(str, *i + ft_strlen(var_name) + 1, ft_strlen(str) - *i - ft_strlen(var_name) - 1));
	*i = *i + ft_strlen(var_value);
	free(str);
	free(var_name);
	free(tmp);
	return (tmp2);
}

void	expansor(t_prs *cmd, t_env **env)
{
	int		i;
	int		j;
	int		single_f;
	int		double_f;
	char	*tmp;
	char	*tmp2;

	i = 0;
	j = 0;
	while (cmd->args[j])
	{
		while (cmd->args[j][i])
		{
			tmp = cmd->args[j];
			single_f = single_quote_dealer(cmd->args[j], i, single_f, double_f);
			double_f = double_quote_dealer(cmd->args[j], i, single_f, double_f);
			if (cmd->args[j][i] == '$' && !single_f)
				tmp2 = expand_var(tmp, &i, env);
			cmd->args[j] = tmp2;
			i++;
		}
		i = 0;
		j++;
	}
}

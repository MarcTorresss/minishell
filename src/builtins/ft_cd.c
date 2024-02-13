/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:16:47 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/13 18:43:55 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_oldpwd(t_env **env, t_env **exp, char *value)
{
	char	*str;
	char	*pwd;

	if (!value)
	{
		printf("\n");
		pwd = getcwd(NULL, 0);
	}
	else
		pwd = value;
	str = ft_strjoin(" OLDPWD=", pwd);
	ft_export(exp, env, str);
	free(pwd);
	free(str);
	pwd = getcwd(NULL, 0);
	str = ft_strjoin(" PWD=", pwd);
	ft_export(exp, env, str);
	free(pwd);
	free(str);
}

void	cd_prev_dir(t_env **env, t_env **exp)
{
	t_env	*tmp;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	tmp = find_env(exp, "OLDPWD");
	if (tmp && tmp->value)
	{
		exit_value(0);
		if (!tmp->value[0])
			set_oldpwd(env, exp, 0);
		else
		{
			if (try_path(tmp->value))
			{
				set_oldpwd(env, exp, old_pwd);
				ft_pwd();
			}
		}
		return ;
	}
	ft_fprintf(2, "minishell: cd: OLDPWD not set\n");
	exit_value(1);
}

void	cd_home(t_env **exp)
{
	t_env	*tmp;

	tmp = find_env(exp, "HOME");
	if (tmp && tmp->value && tmp->value[0])
		try_path(tmp->value);
	else
	{
		exit_value(1);
		ft_fprintf(2, "minishell: cd: HOME not set\n");
	}
}

void	ft_cd(t_env **env, t_env **exp, char *input)
{
	if (input[0] == '-' && (!input[1] || input[1] == ' '))
		cd_prev_dir(env, exp);
	else if (input[0] == '~' && (!input[1] || input[1] == ' '))
		cd_home(exp);
	else if (input[0] != ' ')
		try_path(input);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:16:47 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/05 19:45:29 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_oldpwd(t_env **env, t_env **exp, char *value)
{
	char	*str;
	char	*pwd;

	if (!value)
	{
		ft_printf("\n");
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

void	try_path(t_env **env, t_env **exp, char *path)
{
	char	*old_pwd;
	char	*msg;

	old_pwd = getcwd(NULL, 0);
	msg = ft_strjoin("minishell: cd: ", path);
	if (chdir(path))
	{
		perror(msg);
		//g_exit = 1;
		free(old_pwd);
	}
	else
	{
		set_oldpwd(env, exp, old_pwd);
		ft_pwd();
	}
	free(msg);
}

void	cd_prev_dir(t_env **env, t_env **exp)
{
	t_env	*tmp;

	tmp = find_env(exp, "OLDPWD");
	if (tmp)
	{
		if (tmp->value)
		{
			if (!tmp->value[0])
				set_oldpwd(env, exp, 0);
			else
				try_path(env, exp, tmp->value);
			return ;
		}
	}
	ft_printf("minishell: cd: OLDPWD not set\n");
	//g_exit = 1;
}

void	ft_cd(t_env **env, t_env **exp, char *input)
{
	if (input[0] == '/')
		try_path(env, exp, input);
	//if ((input[0] == '.' && (input[1] == '/' || input[1] == '.') || input[0] != '/')
	//	cd_rel_path(env, exp, input);
	if (input[0] == '-' && (!input[1] || input[1] == ' '))
		cd_prev_dir(env, exp);
	// if (input[0] == '~' && (!input[1] || input[1] == ' '))
	// 	cd_home(env, exp, input);
}

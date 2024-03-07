/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:16:47 by rbarbier          #+#    #+#             */
/*   Updated: 2024/03/07 15:49:52 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_oldpwd(t_env **env, t_env **exp, char *value)
{
	char	*str;
	char	*pwd;

	if (!value)
		pwd = getcwd(NULL, 0);
	else
		pwd = value;
	str = ft_strjoin("OLDPWD=", pwd);
	export_process(exp, env, str);
	free(pwd);
	free(str);
	pwd = getcwd(NULL, 0);
	str = ft_strjoin("PWD=", pwd);
	export_process(exp, env, str);
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
		if (!tmp->value[0])
		{
			set_oldpwd(env, exp, 0);
			ft_fprintf(1, "\n");
		}
		else
		{
			if (chdir(tmp->value))
				return (msg_return("cd", tmp->value,
						"No such file or directory", 1));
			set_oldpwd(env, exp, old_pwd);
			ft_pwd(0);
		}
	}
	else
		msg_return("cd", 0, "OLDPWD not set", 1);
}

void	cd_home(t_env **exp)
{
	t_env	*tmp;
	char	*old_pwd;
	
	old_pwd = getcwd(NULL, 0);
	tmp = find_env(exp, "HOME");
	if (tmp && tmp->value && tmp->value[0])
	{
		if (chdir(tmp->value))
			return (msg_return("cd", tmp->value, "No such file or directory",
					1));
		set_oldpwd(exp, exp, old_pwd);
	}
	else
		msg_return("cd", 0, "HOME not set", 1);
}

void	ft_cd(t_env **env, t_env **exp, char **cmd)
{
	exit_status(0);
	if (!cmd[1] || (cmd[1][0] == '~' && !cmd[1][1]))
		return (cd_home(exp));
	else if (cmd[1][0] == '-' && !cmd[1][1])
		cd_prev_dir(env, exp);
	else
	{
		if (chdir(cmd[1]))
			return (msg_return("cd", cmd[1], "No such file or directory", 1));
		set_oldpwd(env, exp, 0);
	}
}

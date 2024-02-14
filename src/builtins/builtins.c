/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:02:53 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/14 15:58:56 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		ft_fprintf(1, "%s=", tmp->name);
		if (tmp->value)
			ft_fprintf(1, "%s\n", tmp->value);
		tmp = tmp->next;
	}
}

void	ft_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	printf("%s\n", tmp);
	free(tmp);
}

int	ft_isbuiltin(char **cmd, t_env **env, t_env **exp)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(exp, cmd[0]);//ft_echo(exp, cmd)
	else if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(env, exp, cmd[1]);
	else if (!ft_strcmp(cmd[0], "env"))
	{
		if (cmd[1])
		{
			printf("env: %s: No such file or directory\n", cmd[1]);
			exit_value(127);
			return (1); 
		}
		ft_env(env);//ft_env(env, cmd);
	}
	else if (!ft_strcmp(cmd[0], "exit"))
		exit(exit_value(0));
	else if (!ft_strcmp(cmd[0], "unset"))
		ft_unset(env, exp, cmd);
	else if (!ft_strcmp(cmd[0], "export")) 
		ft_export(exp, env, cmd);
	else
		printf("not a built in\n");
	return (0);
}

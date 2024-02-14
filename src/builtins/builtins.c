/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:02:53 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/14 11:14:43 by rbarbier         ###   ########.fr       */
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

int	ft_isbuiltin(char *input, t_env **env, t_env **exp)
{
	if (!ft_strncmp(input, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(input, "echo", 4))
		ft_echo(exp, input + 6);
	else if (!ft_strncmp(input, "cd", 2))
		ft_cd(env, exp, input + 3);
	else if (!ft_strncmp(input, "env", 3))
		ft_env(env);
	else if (!ft_strncmp(input, "exit", 4))
		exit(exit_value(0));
	else if (!ft_strncmp(input, "unset", 5))
		ft_unset(env, exp, input);
	else if (!ft_strncmp(input, "export", 6)) 
		ft_export(exp, env, input + 6);
	else
		printf("not a built in\n");
	return (0);
}
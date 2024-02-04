/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:02:53 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/04 19:26:49 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		ft_printf("%s=", tmp->name);
		if (tmp->value)
			ft_printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
}

void	ft_pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
}

int	ft_isbuiltin(char *input, t_env **env, t_env **exp)
{
	if (!ft_strncmp(input, "pwd", 3))
		ft_pwd();
	//else if (!ft_strncmp(input, "echo", 4))
	//	ft_echo();
	// else if (!ft_strncmp(input, "cd", 2))
	// 	ft_cd();
	else if (!ft_strncmp(input, "env", 3))
		ft_env(env);
	// else if (!ft_strncmp(input, "exit", 4))
	// 	ft_exit();
	else if (!ft_strncmp(input, "unset", 5))
		ft_unset(env, exp, input);
	else if (!ft_strncmp(input, "export", 6))
		ft_export(exp, env, input + 6);
	else
		printf("not a built in\n");
	return (0);
}
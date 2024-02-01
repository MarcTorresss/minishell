/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:02:53 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/01 17:20:24 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	 ft_unset(t_env **env, char *name)
// {
// 	t_env	*tmp;
// 	t_env	*prev;

// 	tmp = *env;
// 	if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
// 	{
// 		(*env)->next = tmp->next;
// 		ft_env_del(tmp);
// 	}
// 	else
// 	{
// 		prev = tmp;
// 		tmp = tmp->next;
// 		while (tmp)
// 		{
// 			if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
// 			{
// 				prev->next = tmp->next;
// 				ft_env_del(tmp);
// 			}
// 			else
// 				tmp = tmp->next;
// 			prev = prev->next;
// 		}
// 	}
// }

void	ft_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

void	ft_pwd(void)
{
	printf("%s\n", getcwd(NULL, 0));
}

int	ft_isbuiltin(char *input, t_env **env)
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
	// else if (!ft_strncmp(input, "unset", 5))
	// 	ft_unset(env, name);
	// else if (!ft_strncmp(input, "export", 6))
	// 	ft_export();
	else
		printf("not a built in\n");
	return (0);
}
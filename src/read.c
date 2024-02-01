/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:45:55 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/01 20:18:47 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int argc, char **argv, char **envd)
{
	t_env	*env;
	char	*prompt;

	argc++;
	(*argv)++;
	init_envd(envd, &env);
	while (1)
	{
		prompt = readline("\033[1;32mminishell: \033[0m");
		ft_isbuiltin(prompt, &env);
		//printf("%s\n", prompt);
	}
    return 0;
}
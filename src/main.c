/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:45:55 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/04 12:28:49 by rbarbier         ###   ########.fr       */
/*                                                                 +           */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int argc, char **argv, char **envd)
{
	//t_env	*env;
	//t_env	*exp;
	char	*prompt;
	t_lxr	*lxr = NULL;
	t_cmd	*table = NULL;

	(void)envd;
	argc++;
	(*argv)++;
	//init_envd(envd, &env, &exp);
	while (1)
	{
		prompt = readline("\033[1;32mminishell: \033[0m");
		ft_lexer(prompt, &lxr);
		ft_parser(table, &lxr);
		//ft_isbuiltin(prompt, &env, &exp);
		//printf("%s\n", prompt);
	}
    return 0;
}
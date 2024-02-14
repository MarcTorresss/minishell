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
	t_env	*env;
	t_env	*exp;
	t_cmd	*cmd;
	char	*prompt;
	int		i;
	//t_lxr	*lxr = NULL;

	//(void)envd;
	i = 0;
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		exit_msg("Error: malloc failed\n", 2);
	(void)argv;
	if (argc > 1)
	{
		printf("Error: minishell does not take any arguments\n");
		return (1);
	}
	env = NULL;
	exp = NULL;
	init_envd(envd, &env, &exp);
	while (1)
	{
		prompt = readline("\033[1;32mminishell: \033[0m");
		cmd->args = ft_split(prompt, ' ');
		expansor(cmd, &env);
		while (cmd->args[i])
		{
			printf("%s\n", cmd->args[i]);
			i++;
		}
		i = 0;
		free(prompt);
		free(cmd->args);

		//ft_lexer(prompt, lxr);
		//ft_isbuiltin(prompt, &env, &exp);
		//printf("%s\n", prompt);
	}
    return 0;
}
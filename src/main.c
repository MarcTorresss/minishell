/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:45:55 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/04 12:28:49 by rbarbier         ###   ########.fr       */
/*                                                                
	+           */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_parser(t_cmd *cmd)
{
	int	i = 0;
	int	j = 0;
	t_rd	*tmp;
	
	while (cmd != NULL)
	{
		j = 0;
		tmp = cmd->redir;
		while (cmd->args[j] != NULL)
		{
			i = 0;
			ft_fprintf(1, "cmd->args[%d] = %s\n", j, cmd->args[j]);
			while (tmp != NULL)
			{
				ft_fprintf(1, "tmp->redir->type = %d\n", tmp->type);
				ft_fprintf(1, "tmp->redir->file = %s\n", tmp->file);
				tmp = tmp->next;
			}
			while (cmd->args[j][i] != '\0')
			{
				ft_fprintf(1, "cmd->args[%d][%d] = %c\n", j, i, cmd->args[j][i]);
				i++;
			}
			j++;
		}
		cmd = cmd->next;
	}
}

int	main(int argc, char **argv, char **envd)
{
	t_env	*env;
	t_env	*exp;
	t_cmd	*cmd;
	char	*prompt;
	t_lxr	*lxr;

	cmd = NULL;
	lxr = NULL;
	env = NULL;
	exp = NULL;
	//(void)envd;
	(void)argv;
	if (argc > 1)
	{
		printf("Error: minishell does not take any arguments\n");
		return (1);
	}
	init_envd(envd, &env, &exp);
	while (1)
	{
		prompt = readline("\033[1;32mminishell: \033[0m");
		if (ft_lexer(prompt, &lxr) == 0)
		{
			if (ft_parser(&cmd, &lxr) != -1)
			{
				print_parser(cmd);
				ft_heredoc(cmd);
				expansor(cmd, &env);
				executor(cmd, &env, &exp);
			}
		}
		ft_clean_lxr_prs(&cmd, &lxr);
		lxr = NULL;
		cmd = NULL;
	}
	return (0);
}

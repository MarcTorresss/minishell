/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:31:07 by martorre          #+#    #+#             */
/*   Updated: 2024/03/07 11:46:05 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_lex(t_lxr *lxr)
{
	ft_fprintf(1, "\nStack Lxr\n");
	while (lxr != NULL)
	{
		ft_fprintf(1, "\nword = %s -> sig = %d\n", lxr->word, lxr->sign);
		lxr = lxr->next;
	}
}

void	print_parser(t_cmd *cmd)
{
	int		i;
	int		j;
	int		z;
	t_rd	*tmp;

	i = 0;
	j = 0;
	z = 0;
	while (cmd != NULL)
	{
		j = 0;
		ft_fprintf(1, "\nTOKENNN ---- %i\n", z);
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
			/*while (cmd->args[j][i] != '\0')
			{
				ft_fprintf(1, "cmd->args[%d][%d] = %c\n", j, i,
					cmd->args[j][i]);
				i++;
			}*/
			j++;
			z++;
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
	rl_catch_signals = 0;
	(void)argv;
	if (argc > 1)
	{
		printf("Error: minishell does not take any arguments\n");
		return (1);
	}
	init_envd(envd, &env, &exp);
	init_signals(1);
	while (1)
	{
		prompt = readline("\033[1;32mminishell: \033[0m");
		if (prompt == NULL)
		{
			ft_fprintf(1, "exit\n");
			break ;
		}
		if (ft_lexer(prompt, &lxr) == 0)
		{
			if (ft_parser(&cmd, &lxr) != -1)
			{
				//print_lex(lxr);
				//print_parser(cmd);
				ft_heredoc(cmd, &env);
				if (!expansor(cmd, &env))
					executor(cmd, &env, &exp);
			}
		}
		ft_clean_lxr_prs(&cmd, &lxr);
		lxr = NULL;
		cmd = NULL;
	}
	return (0);
}

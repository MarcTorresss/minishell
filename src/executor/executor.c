/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:28:54 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/16 16:34:22 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_files(t_cmd *cmd, t_exec *exec)
{
	if (cmd->type == INPUT_REDIR)
	{
		exec->infile = open(cmd->args[0], O_RDONLY); 
		if (exec->infile < 0) // test if input file can be opened
		{
			error_pipex(3, cmd->args[0]);
			return (1);
		}
	}
	while (cmd->next)
		cmd = cmd->next;
	if (cmd->type == OUTPUT_REDIR)
	{
		exec->outfile = open(cmd->args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (exec->outfile < 0) // test if output file can be created or truncated
		{
			error_pipex(3, cmd->args[1]); // the output file should be changed to the right file
			return (1);
		}
	}
	return (0);
}

void	executor(t_cmd *cmd, t_env **env, t_env **exp)
{
	t_exec	exec;

	if (check_files(cmd, &exec))
		return ;
	pipex_main(cmd, env, exp, &exec);
	(void)cmd;
	(void)env;
	(void)exp;
}
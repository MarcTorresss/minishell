/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_input_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:30:41 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/16 14:58:16 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	input_check(char **argv, t_exec *exec, int child)
{
	if (child == 1)
	{
		exec->infile = open(argv[1], O_RDONLY);
		if (exec->infile < 0)
			error_pipex(3, argv[1]);
	}
	else
	{
		exec->outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0000644);
		if (exec->outfile < 0)
			error_pipex(3, argv[4]);
	}
}
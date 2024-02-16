/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:36:12 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/16 14:56:57 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	put_exitcode(int err_type)
{
	if (err_type >= 1 && err_type <= 8)
		exit(1);
	else if (err_type == 9)
		exit(127);
	else if (err_type == 10)
		exit(126);
}

void	error_pipex(int err_type, char *name)
{
	write(2, "pipex: ", 7);
	if (err_type == 1)
		write(2, "number of arguments not valid\n", 30);
	else if (err_type == 3)
		perror(name);
	else if (err_type == 4)
		perror(name);
	else if (err_type == 5)
		perror("pipe issue");
	else if (err_type == 6)
		perror("fork issue");
	else if (err_type == 7)
		perror("memory issue");
	else if (err_type == 9)
	{
		write(2, name, ft_strlen(name));
		write(2, ": command not found\n", 20);
	}
	else if (err_type == 10)
		perror(name);
	put_exitcode(err_type);
}
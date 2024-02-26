/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:02:05 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/26 19:09:51 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_pwd(char **cmd)
{
	char	*tmp;

	if (cmd && cmd[1])
		return (msg_return("pwd", 0, "too many arguments", 1));
	tmp = getcwd(NULL, 0);
	ft_fprintf(1, "%s\n", tmp);
	free(tmp);
	exit_status(0);
}

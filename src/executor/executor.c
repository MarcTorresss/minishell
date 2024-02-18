/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:28:54 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/18 14:53:42 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	executor(t_cmd *cmd, t_env **env, t_env **exp)
{
	t_exec	exec;

	pipex_main(cmd, env, exp, &exec);
}
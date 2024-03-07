/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:26:25 by rbarbier          #+#    #+#             */
/*   Updated: 2024/03/07 15:48:18 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	numeric_check(char *arg)
{
	int		i;

	i = 0;
	if (arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_fprintf(2, "exit\nminishell: exit: %s: numeric argument required\n", arg);
			exit(255);
		}
		i++;
	}
}
void	limit_number(char *arg)
{
	int		negativ;
	char	*orig;

	orig = arg;
	negativ = 0;
	if (*arg == '-')
	{
		negativ = 1;
		arg++;
	}
	while (*arg == '0' && *(arg + 1) != '\0')
		arg++;
	if (ft_strlen(arg) > 19)
		ft_fprintf(2, "exit\nminishell: exit: %s: numeric argument required\n", orig);
	else if (ft_strlen(arg) == 19 && ft_strcmp(arg, "9223372036854775807") > 0 && !negativ)
		ft_fprintf(2, "exit\nminishell: exit: %s: numeric argument required\n", orig);
	else if (ft_strlen(arg) == 19 && ft_strcmp(arg, "9223372036854775808") > 0 && negativ)
		ft_fprintf(2, "exit\nminishell: exit: %s: numeric argument required\n", orig);
	else
		return ;
	exit(255);
}

void	ft_exit(char **cmd)
{
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	if (cmd[1])
	{
		numeric_check(cmd[1]);
		limit_number(cmd[1]);
		ret = ft_atoi(cmd[1]);
	}
	if (cmd[1] && cmd[2])
	{
		ft_fprintf(2, "exit\nminishell: exit: too many arguments\n");
		exit_status(1);
		return ;
	}
	ft_fprintf(2, "exit\n");
	exit(ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:26:25 by rbarbier          #+#    #+#             */
/*   Updated: 2024/03/13 17:39:07 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	numeric_check(char *arg)
{
	int		digit;
	int		i;

	i = 0;
	digit = 0;
	if ((arg[i] == '+' && arg[i + 1] != 0)
		|| (arg[i] == '-' && arg[i + 1] != 0))
		i++;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]))
			digit = 1;
		while (arg[i] == ' ')
			i++;
		if (!arg[i] && !digit)
			return (ft_fprintf(2, LIMIT, arg), exit(255), (void)0);
		else if (!arg[i] && digit)
			return ;
		if (!ft_isdigit(arg[i]))
		{
			ft_fprintf(2, LIMIT, arg);
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
		ft_fprintf(2, LIMIT, orig);
	else if (ft_strlen(arg) == 19
		&& ft_strcmp(arg, "9223372036854775807") > 0 && !negativ)
		ft_fprintf(2, LIMIT, orig);
	else if (ft_strlen(arg) == 19
		&& ft_strcmp(arg, "9223372036854775808") > 0 && negativ)
		ft_fprintf(2, LIMIT, orig);
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
	if (cmd[1] && !ft_strcmp(cmd[1], "--"))
		return (ft_fprintf(1, "exit\n"), exit(0), (void)0);
	else if (cmd[1] && !cmd[1][0])
	{
		ft_fprintf(2, "exit\nminishell: exit: : numeric argument required\n");
		exit(255);
	}
	else if (cmd[1])
	{
		numeric_check(cmd[1]);
		limit_number(cmd[1]);
		ret = ft_atoi(cmd[1]);
	}
	if (cmd[1] && cmd[2])
	{
		ft_fprintf(2, "exit\nminishell: exit: too many arguments\n");
		return (exit_status(1), (void)0);
	}
	exit(ret);
}

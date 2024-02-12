/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:26:40 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/12 14:29:53 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_value(int value)
{
	static int	prev = 0;
	int			ret;

	ret = prev;
	prev = value;
	return (ret);
}

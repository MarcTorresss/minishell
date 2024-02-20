/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:55:34 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/16 16:09:38 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	single_quote_dealer(char *str, int i, int single_f, int double_f)
{
	if (!double_f)
	{
		if (str[i] == '\'' && single_f)
			single_f = 0;
		else if (str[i] == '\'' && !single_f)
			single_f = 1;	
	}
	return (single_f);
}

int	double_quote_dealer(char *str, int i, int single_f, int double_f)
{
	if (!single_f)
	{
		if (str[i] == '\"' && double_f)
			double_f = 0;
		else if (str[i] == '\"' && !double_f)
			double_f = 1;	
	}
	return (double_f);
}
char	*get_var_name(char *str, int i)
{
	int		j;
	char	*var_name;

	j = 0;
	while (str[i + j] && (ft_isalnum(str[i + j]) || str[i + j] == '_'))
		j++;
	var_name = ft_substr(str, i, j);
	return (var_name);
}

char	*remove_char_at(char *str, int i)
{
	char	*tmp;

	tmp = ft_substr(str, 0, i);
	tmp = ft_join_n_destroy(tmp, ft_substr(str, i + 1, ft_strlen(str) - i - 1), 2);
	free(str);
	return (tmp);
}
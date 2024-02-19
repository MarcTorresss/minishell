/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_n_destroy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:08:00 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/19 15:49:40 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join_n_destroy(char *s1, char *s2, int to_free)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	if (to_free == 1)
		free(s1);
	else if (to_free == 2)
		free(s2);
	else if (to_free == 3)
	{
		free(s1);
		free(s2);
	}
	return (new);
}

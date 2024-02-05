/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_to_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:07:06 by martorre          #+#    #+#             */
/*   Updated: 2024/02/01 15:18:13 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ascii_chars(char *str, t_lxr *lxr)
{
    int i;

    i = 0;
    if (str[i] == GREAT && str[i + 1] == GREAT)
        lxr->word = ">>";
    else if (str[i] == LESS && str[i + 1] == LESS)
        lxr->word = "<<";
}

void    ascii_char(char c, t_lxr *lxr)
{
    int i;

    i = 0;
    if (c == GREAT)
        lxr->word = ">";
    else if (c == LESS)
        lxr->word = "<";
    else if (c == PIPE)
        lxr->word = "|";
    else if (c == DOLLAR)
        lxr->word = "$";
    else if (c == QUOTE_ONE)
        lxr->word = QUOTE_ONE;
    else if (c == QUOTE_TOW)
        lxr->word = QUOTE_TOW;
}

int ft_convert(char *str, t_lxr *lxr)
{
    int i;

    i = 0;
    while (str[i] != '\0' && ft_isspace(str[i]) == 0)
    {
        //controlar caso de comillas
    }
        i++;
    if (i == 1)
        ascii_char(str[i], lxr);
    else if (i == 2)
        ascii_chars(str, lxr);
    else
        lxr->word = ft_substr(str, 0, i);
    return (i);
}

t_lxr   *init_lxr(void)
{
    t_lxr   *new;

    new = malloc(sizeof(t_lxr));
    if (!new)
        return (NULL);
    new->word = NULL;
    new->next = NULL;
    return (new);
}

int str_to_list(char *str, t_lxr *lxr)
{
    t_lxr   *new;
    int     i;

    i = 0;
    while (str[i] != '\0')
    {
        if (ft_isspace(str[i]) == 1)
            i++;
        else
        {
            new = init_lxr();
            if (!new)
                return (1);
            ft_lxr_addback(lxr, new);
            i = ft_convert(ft_substr(str, i, ft_strlen(str)), lxr);
        }
    }
    return (0);
}

/*int main()
{
    t_lxr   *new;
    str_to_list("ls >> aaaa < cat", new);
	ft_printf("\nStack Lxr\n");
	while (new != NULL)
	{
		ft_printf("%s\n", new->word);
		new = new->next;
	}
}*/
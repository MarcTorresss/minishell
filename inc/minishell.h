/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:44:42 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/04 19:16:30 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

#define PIPE_AC 124
#define DOLLAR_AC 36
#define LESS_AC 60
#define GREAT_AC 62
#define QUOTE_ONE 39
#define QUOTE_TOW 34

typedef enum s_sign
{
    PIPE,
    LESS,
    LESS_T,
    GREAT,
    GREAT_T,
    NOTH = 0
}   t_sign;

typedef struct  s_lexer
{
    char            *word;
    t_sign          sign;
    struct t_lxr   *next;
}   t_lxr;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

/*******************************	LEXER	*******************************/

int     ft_isquote(char c);
int     ft_isspace(char c);
t_lxr   *ft_last_lxr(t_lxr *lxr);
void    ft_lxr_addback(t_lxr *lxr, t_lxr *new);

/*******************************	****	*******************************/

void	init_envd(char **envd, t_env **env, t_env **exp);
char	*find_env_var(char *name, t_env **env_var);
int		ft_isbuiltin(char *input, t_env **env, t_env **exp);
void	ft_env_del(t_env *env);
void	ft_unset(t_env **env, t_env **exp, char *input);
void	ft_env(t_env **env);
void	ft_export(t_env **exp, t_env **env, char *input);
int		new_env_var(char *name, char *value, t_env **env_var);
char	*get_name(char *input);
char	*get_value(char *input);
int		update_value(char *name, char *value, t_env **exp);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:44:42 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/14 18:32:54 by rbarbier         ###   ########.fr       */
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
# include <signal.h>

//  ASCII

# define PIPE_AC 124
# define DOLLAR_AC 36
# define LESS_AC 60
# define GREAT_AC 62
# define QUOTE_ONE 39
# define QUOTE_TOW 34

// SIGNALS

# define CTRL_C SIGINT
# define CTRL_SLASH SIGQUIT

typedef enum s_sign
{
    NOTH = 0,
    PIPE,
    LESS,
    LESS_T,
    GREAT,
    GREAT_T
}   t_sign;

typedef enum s_token_type
{
    REDIRECT,
    INVALID,
    WORD
}   t_type;

typedef struct s_expansion {
    int i;
    int j;
    int single_f;
    int double_f;
} t_expansion;

typedef struct  s_lexer
{
    char            *word;
    t_sign          sign;
    struct s_lexer  *next;
    struct s_lexer  *prev;
}       t_lxr;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}       t_env;

typedef struct s_parser
{
    int             qtt_args;
    char            **args;
	t_type			type;
    struct s_parser *next;
}       t_cmd;

/*******************************	LEXER	*******************************/

int     ft_lexer(char *str, t_lxr *lxr);
int     ft_isquote(char c);
int     ft_isspace(char c);
int     ft_issign(char c);
t_lxr   *ft_last_lxr(t_lxr *lxr);
t_lxr	*ft_lxr_addback(t_lxr *lxr, t_lxr *new);

/*******************************  EXPANSOR  *******************************/

void	expansor(t_cmd *cmd, t_env **env);
char	*expand_var(char *str, int *i, t_env **env);
char	*get_var_name(char *str, int i);
int		double_quote_dealer(char *str, int i, int single_f, int double_f);
int		single_quote_dealer(char *str, int i, int single_f, int double_f);
char	*remove_char_at(char *str, int i);

/*******************************	****	*******************************/

void	export_process(t_env **exp, t_env **env, char *cmd);
void	exit_msg(char *msg, int status);
int		forbidden_char(char *input);
void    init_envd(char **envd, t_env **env, t_env **exp);
int     ft_isbuiltin(char **cmd, t_env **env, t_env **exp);
void    ft_env_del(t_env *env);
void    ft_unset(t_env **env, t_env **exp, char **cmd);
void    ft_env(t_env **env);
void    ft_export(t_env **exp, t_env **env, char **cmd);
void	new_env_var(char *name, char *value, t_env **env_var);
char    *get_name(char *input);
char    *get_value(char *input);
int     update_value(char *name, char *value, t_env **exp);
t_env   *find_env(t_env **env, char *name);
void    ft_pwd(void);
void    ft_cd(t_env **env, t_env **exp, char *input);
int     try_path(char *path);
void    ft_echo(t_env **exp, char *input);
int		exit_value(int value);

#endif
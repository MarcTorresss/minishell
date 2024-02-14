/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:44:42 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/14 15:37:51 by martorre         ###   ########.fr       */
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

// ERRORS

#define ERROR_TOKEN_P "syntax error near unexpected token '|'\n"
#define ERROR_TOKEN_L "syntax error near unexpected token '<'\n"
#define ERROR_TOKEN_LL "syntax error near unexpected token '<<'\n"
#define ERROR_TOKEN_G "syntax error near unexpected token '>'\n"
#define ERROR_TOKEN_GG "syntax error near unexpected token '>>'\n"
#define ERROR_TOKEN_NL "syntax error near unexpected token\n"

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
    HEREDOC,
    INPUT_REDIR,
    OUTPUT_REDIR,
    APPEND_TO_END,
    INVALID,
    NOTHING
}   t_type;

typedef struct  s_lexer
{
    char            *word;
    t_sign          sign;
    struct s_lexer  *next;
}       t_lxr;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}       t_env;

typedef struct s_comand
{
    char            **args;
	t_type			type;
    struct s_comand *next;
}       t_cmd;

/*******************************	LEXER	*******************************/

int     ft_lexer(char *str, t_lxr **lxr);
int     ft_isquote(char c);
int     ft_isspace(char c);
int     ft_issign(char c);
void    lexer_clear(t_lxr *lxr);
t_lxr   *ft_last_lxr(t_lxr *lxr);
t_lxr	*ft_lxr_addback(t_lxr *lxr, t_lxr *new);
void	print_lex(t_lxr *lxr);

/*******************************  PARSER  *******************************/

int     ft_parser(t_cmd *table, t_lxr **lxr);
int     ft_sizelst(t_lxr *list);
t_cmd   *init_parser(void);
t_cmd	*ft_cmd_addback(t_cmd *table, t_cmd *new);
char    **free_all(char **mat, int i);


/*******************************	****	*******************************/

void    init_envd(char **envd, t_env **env, t_env **exp);
int     ft_isbuiltin(char *input, t_env **env, t_env **exp);
void    ft_env_del(t_env *env);
void    ft_unset(t_env **env, t_env **exp, char *input);
void    ft_env(t_env **env);
void    ft_export(t_env **exp, t_env **env, char *input);
int     new_env_var(char *name, char *value, t_env **env_var);
char    *get_name(char *input);
char    *get_value(char *input);
int     update_value(char *name, char *value, t_env **exp);
t_env   *find_env(t_env **env, char *name);
void    ft_pwd(void);
void    ft_cd(t_env **env, t_env **exp, char *input);
int     try_path(char *path);
void    ft_echo(t_env **exp, char *input);

#endif
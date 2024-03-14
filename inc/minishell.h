/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:31:21 by martorre          #+#    #+#             */
/*   Updated: 2024/03/14 11:20:22 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include "../readline/history.h"
# include "../readline/readline.h"
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <unistd.h>

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

# define ERROR_TOKEN_P "minishell: syntax error near unexpected token `|'\n"
# define ERROR_TOKEN_L "minishell: syntax error near unexpected token `<'\n"
# define ERROR_TOKEN_LL "minishell: syntax error near unexpected token `<<'\n"
# define ERROR_TOKEN_G "minishell: syntax error near unexpected token `>'\n"
# define ERROR_TOKEN_GG "minishell: syntax error near unexpected token `>>'\n"
# define ERROR_TOKEN_NL \
"minishell: syntax error near unexpected token `newline'\n"
# define ERROR_TOKEN_UN "minishell: syntax error near unexpected token\n"
# define ERR_PIPE "pipe issue"
# define ERR_FORK "fork issue"
# define ERR_EXEC "exec issue"
# define ERR_FILE "file issue"
# define ERR_ARG "too many arguments"
# define ERR_MALLOC "malloc issue"
# define ERR_OPEN "open issue"
# define ERR_CMD_NOT_FOUND "command not found"
# define ERR_NO_FILE "No such file or directory"
# define ERR_NO_PERM "Permission denied"
# define LIMIT "exit\nminishell: exit: %s: numeric argument required\n"
# define NOTFOUND "minishell: %s: command not found\n"

// STRUCTURES

typedef enum s_sign
{
	NOTH = 0,
	PIPE,
	LESS,
	LESS_T,
	GREAT,
	GREAT_T
}						t_sign;

typedef enum s_token_type
{
	HEREDOC = 0,
	INPUT_REDIR,
	OUTPUT_REDIR,
	APPEND_TO_END,
	INVALID,
	NOTHING
}						t_type;

typedef struct s_expansion
{
	int					i;
	int					j;
	int					single_f;
	int					double_f;
}						t_expansion;

typedef struct s_lexer
{
	char				*word;
	t_sign				sign;
	struct s_lexer		*next;
}						t_lxr;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_redirect
{
	t_type				type;
	char				*file;
	struct s_redirect	*next;
}						t_rd;

typedef struct s_comand
{
	char				**args;
	t_rd				*redir;
	struct s_comand		*next;
}						t_cmd;

typedef struct s_pipe
{
	int					pipe_ends[2];
	pid_t				*pid;
	int					original_stdout;
	int					original_stdin;
	int					n_cmds;
	int					infile_fd;
	int					outfile_fd;
	char				**cmd_paths;
	char				*cmd;
}						t_pipe;

/*******************************	LEXER	*******************************/

int						ft_lexer(char *str, t_lxr **lxr);
int						ft_isquote(char c);
int						ft_isspace(char c);
int						ft_issign(char c);
void					lexer_clear(t_lxr **lxr);
t_lxr					*ft_last_lxr(t_lxr *lxr);
t_lxr					*ft_lxr_addback(t_lxr *lxr, t_lxr *new);
void					print_lex(t_lxr *lxr);
t_lxr					*init_lxr(void);
int						init_word(char *str);
void					print_lex(t_lxr *lxr);

/*******************************  PARSER  *******************************/

int						ft_parser(t_cmd **table, t_lxr **lxr);
int						ft_sizelst(t_lxr *list);
t_cmd					*init_parser(void);
void					ft_cmd_addback(t_cmd **table, t_cmd *new);
char					**free_all(char **mat, int i);
void					ft_clean_lxr_prs(t_cmd **table, t_lxr **lxr);
void					parser_clear(t_cmd **table);
t_rd					*init_redir(void);
t_rd					*ft_last_rd(t_rd *redir);
void					ft_addback_redir(t_rd **redir, t_rd *new);
int						ft_issigntoken(char c);
int						ft_heredoc(t_cmd *cmd, t_env **env);
int						check_error(t_lxr *lxr);
int						count_args(t_lxr *lxr);
int						check_signs(t_lxr *lxr, int qtt);
int						init_signals(int status);
int						check_pipes(t_lxr *lxr);
void					print_parser(t_cmd *cmd);

/*******************************  EXPANSOR  *******************************/

int						expansor(t_cmd *cmd, t_env **env);
char					*expand_var(char *str, int *i, t_env **env);
char					*get_var_name(char *str, int i);
int						double_quote_dealer(char *str, int i, int single_f,
							int double_f);
int						single_quote_dealer(char *str, int i, int single_f,
							int double_f);
char					*remove_char_at(char *str, int i);
void					question_mark(char **var_name, char **var_value);
int						expand(char **str, int j, t_env **env, int quote_rem);

/**********************  ENVIRONMENT / BUILTINS  **************************/

void					export_process(t_env **exp, t_env **env, char *cmd);
void					msg_exit(char *cmd, char *arg, char *msg, int status);
void					msg_return(char *cmd, char *arg, char *msg, int status);
int						forbidden_char(char *input);
void					init_envd(char **envd, t_env **env, t_env **exp);
void					ft_unset(t_env **env, t_env **exp, char **cmd);
void					ft_env(t_env **env, char **cmd);
void					ft_export(t_env **exp, t_env **env, char **cmd);
void					new_env_var(char *name, char *value, t_env **env_var);
char					*get_name(char *input);
char					*get_value(char *input);
int						update_value(char *name, char *value, t_env **exp,
							int append);
t_env					*find_env(t_env **env, char *name);
void					ft_pwd(char **cmd);
void					ft_cd(t_env **env, t_env **exp, char **cmd);
void					ft_exit(char **cmd);
void					ft_echo(char **args);
int						exit_status(int value);
void					swap_data(t_env *nod1, t_env *nod2);
void					export_print(t_env **exp);

/*******************************  EXECUTOR  *******************************/

int						get_files_redir(t_rd *redir, t_pipe *data);
void					make_redirections(t_pipe *data, t_cmd *cmd);
void					unlink_heredoc(t_cmd *cmd);
char					**env_to_array(t_env **env);
void					check_file(char *file, int mode);
void					save_original_stds(t_pipe *data);
void					reset_original_stds(t_pipe *data);
void					close_pipes(int fd1, int fd2);
int						is_builtin(char **cmd, t_env **env, t_env **exp);
void					child(t_pipe data, t_cmd *cmd, t_env **env,
							t_env **exp);
int						check_paths(t_pipe *data, t_cmd *cmd);
int						check_absolute_path(t_cmd *cmd);
char					**get_paths(t_env **env);
void					executor(t_cmd *cmd, t_env **env, t_env **exp);

#endif

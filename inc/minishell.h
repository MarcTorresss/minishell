/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarbier <rbarbier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:44:42 by rbarbier          #+#    #+#             */
/*   Updated: 2024/02/05 17:30:30 by rbarbier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

#define PIPE 124
#define DOLLAR 36
#define LESS 60
#define GREAT 62
#define QUOTE_ONE 39
#define QUOTE_TOW 34

//int	g_exit = 0;

typedef struct s_lexer
{
	char			*word;
    struct s_lexer	*next;
}   t_lxr;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

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
t_env	*find_env(t_env **env, char *name);
void	ft_pwd(void);
void	ft_cd(t_env **env, t_env **exp, char *input);

#endif
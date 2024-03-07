/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martorre <martorre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:13:43 by martorre          #+#    #+#             */
/*   Updated: 2024/03/07 15:49:23 by martorre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_start_heredoc(t_rd *redir, char *path, t_env **env)
{
	int		fd;
	char	*line;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (-1);
		if (ft_strcmp(line, redir->file) == 0)
		{
			free(line);
			close(fd);
			return (0);
		}
		if (!(ft_strchr(redir->file, '\'')) && !(ft_strchr(redir->file, '\"')))
			expand(&line, 0, env, 0);
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (0);
}

int	ft_heredoc(t_cmd *cmd, t_env **env)
{
	t_rd	*tmp;
	int		i;

	i = 0;
	while (cmd)
	{
		tmp = cmd->redir;
		while (tmp)
		{
			if (tmp->type == HEREDOC)
				if (ft_start_heredoc(tmp, ft_strjoin("/tmp/mini_here",
							ft_itoa(i++)), env) == -1)
					return (-1);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

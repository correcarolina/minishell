/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:00:04 by cacorrea          #+#    #+#             */
/*   Updated: 2025/04/26 22:00:08 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_file(int fd)
{
	if (fd >= 0)
		close(fd);
}

static int	open_file(const char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(filename, 2);
		perror("");
		return (-1);
	}
	return (fd);
}

int	redirection_out(t_list *redir)
{
	int	fd_out;

	fd_out = -1;
	if (redir->type == RD_OUT_A)
	{
		fd_out = open_file(redir->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd_out == -1)
			return (-1);
		dup2(fd_out, STDOUT_FILENO);
		close_file(fd_out);
	}
	else if (redir->type == RD_OUT_T)
	{
		fd_out = open_file(redir->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out == -1)
			return (-1);
		dup2(fd_out, STDOUT_FILENO);
		close_file(fd_out);
	}
	return (0);
}

int	handle_redirection(t_list *redir)
{
	int	fd_in;

	while (redir)
	{
		if (redir->type == RD_HEREDOC)
		{
			if (handle_heredoc(redir->content) == -1)
				return (-1);
		}
		else if (redir->type == RD_IN)
		{
			fd_in = open_file(redir->content, O_RDONLY, 0);
			if (fd_in == -1)
				return (-1);
			dup2(fd_in, STDIN_FILENO);
			close_file(fd_in);
		}
		else if (redir->type == RD_OUT_T || redir->type == RD_OUT_A)
		{
			if (redirection_out(redir) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

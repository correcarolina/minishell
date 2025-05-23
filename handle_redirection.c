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

// This function duplicates fd1 to fd2 and closes fd1.
int	p_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		perror("dup2");
		return (-1);
	}
	if (fd1 != fd2)
	{
		close_file(fd1);
	}
	return (0);
}

// This function opens a file and handles errors.
static int	open_file(const char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)filename, 2);
		if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", 2);
		else if (errno == ENOENT)
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			perror("");
		return (-1);
	}
	return (fd);
}

int	redirection_out(t_redirlst *redir)
{
	int	fd_out;

	fd_out = -1;
	if (redir->type == RD_OUT_A)
	{
		fd_out = open_file(redir->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd_out == -1)
			return (-1);
		if (p_dup2(fd_out, STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (redir->type == RD_OUT_T)
	{
		fd_out = open_file(redir->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd_out == -1)
			return (-1);
		if (p_dup2(fd_out, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	handle_redirection(t_redirlst *redir)
{
	int	fd_in;

	while (redir)
	{
		if (redir->type == RD_HEREDOC)
		{
			if (p_dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
			return (-1);
		}
		else if (redir->type == RD_IN)
		{
			fd_in = open_file(redir->content, O_RDONLY, 0);
			if (fd_in == -1)
				return (-1);
			if (p_dup2(fd_in, STDIN_FILENO) == -1)
				return (-1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 22:00:04 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/08 21:48:08 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		close_fd(fd1);
	}
	return (0);
}

// This function opens a file and handles errors.
static int	open_file(char *filename, int flags, mode_t mode, t_ms *mini)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			ft_print_error(filename, mini, 4);
			mini->exit_status = 1;
		}
		else if (errno == ENOENT)
			ft_print_error(filename, mini, 3);
		else
		{
			ft_putstr_fd("minishell: ", 2);
			perror(filename);
			mini->exit_status = 1;
		}
		return (-1);
	}
	return (fd);
}

int	redirection_out(t_redirlst *redir, t_ms *mini)
{
	int		fd_out;
	char	*file;

	fd_out = -1;
	file = redir->content;
	if (redir->type == RD_OUT_A)
	{
		fd_out = open_file(file, O_CREAT | O_WRONLY | O_APPEND, 0644, mini);
		if (fd_out == -1)
			return (-1);
		if (p_dup2(fd_out, STDOUT_FILENO) == -1)
			return (-1);
	}
	else if (redir->type == RD_OUT_T)
	{
		fd_out = open_file(file, O_CREAT | O_WRONLY | O_TRUNC, 0644, mini);
		if (fd_out == -1)
			return (-1);
		if (p_dup2(fd_out, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

int	handle_redirection(t_redirlst *redir, t_ms *mini)
{
	int	fd_in;

	while (redir)
	{
		if (redir->type == RD_HEREDOC)
		{
			if (p_dup2(redir->heredoc_fd, STDIN_FILENO) == -1)
				return (-1);
			close_fd(redir->heredoc_fd);
		}
		else if (redir->type == RD_IN)
		{
			fd_in = open_file(redir->content, O_RDONLY, 0, mini);
			if (fd_in == -1)
				return (-1);
			if (p_dup2(fd_in, STDIN_FILENO) == -1)
				return (-1);
		}
		else if (redir->type == RD_OUT_T || redir->type == RD_OUT_A)
		{
			if (redirection_out(redir, mini) == -1)
				return (-1);
		}
		redir = redir->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 11:14:49 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/09 13:00:12 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_single_pipe(t_cmdblock *cmd, int pipe_fd[2])
{
	if (cmd->next && pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	close_fd(int fd)
{
	if (fd >= 0)
		close(fd);
}

void	close_2_fds(int fd1, int fd2)
{
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
}

void	inizilize_3fds(int *fd1, int pipe_fd[2])
{
	*fd1 = -1;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
}

void	ft_clear_n_exit(t_ms *mini, int exit_status, int write_fd)
{
	close_fd(write_fd);
	ft_clear_cmdblock(&mini->cmdblocks);
	ms_cleanup(mini);
	exit(exit_status);
}

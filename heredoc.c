/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:52:50 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/09 13:10:49 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signo;

static int	handle_line(t_ms *mini, char **line, char *delim, int quoted_hd)
{
	char	*tmp;

	if (ft_strcmp(*line, delim) == 0)
		return (0);
	if (ft_strchr(*line, '$') && !quoted_hd)
	{
		tmp = ft_expand_heredoc(mini, line);
		if (!tmp)
			return (-1);
		free(*line);
		*line = tmp;
	}
	return (1);
}

static int	process_hd_inpt(t_ms *ms, char *delmitr, int quotd_hd, int write_fd)
{
	char	*line;
	int		res;

	line = readline(AQUA "HEREDOC> " DEFAULT);
	if (!line && g_signo != SIGINT)
	{
		ms->exit_status = getsingal(ms);
		printf("minishell: warning: here-document delimited by \
end-of-file (wanted `%s')\n", delmitr);
		return (0);
	}
	else if (!line && g_signo == SIGINT)
	{
		ms->exit_status = getsingal(ms);
		ft_clear_n_exit(ms, 130, write_fd);
	}
	res = handle_line(ms, &line, delmitr, quotd_hd);
	if (res <= 0)
		return (free(line), 0);
	write(write_fd, line, ft_strlen(line));
	write(write_fd, "\n", 1);
	free(line);
	return (1);
}

static void	here_child(t_ms *mini, char *delimiter, int write_fd)
{
	int	quoted_hd;

	signal(SIGINT, ft_hd_ctrlc);
	quoted_hd = ft_check_delimiter_quote(&delimiter);
	while (process_hd_inpt(mini, delimiter, quoted_hd, write_fd))
		;
	ft_clear_n_exit(mini, 0, write_fd);
}

static int	create_heredoc(t_ms *mini, t_redirlst *current)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
	{
		close_fd(fd[0]);
		close(mini->stdinout_copy[0]);
		close(mini->stdinout_copy[1]);
		here_child(mini, current->content, fd[1]);
	}
	close(fd[1]);
	status = ft_wait_heredoc(pid);
	current->heredoc_fd = fd[0];
	return (status);
}

int	handle_heredocs(t_cmdblock *cmdblocks, t_ms *mini)
{
	t_cmdblock	*actual_cmd;
	t_redirlst	*current;

	actual_cmd = cmdblocks;
	while (actual_cmd)
	{
		current = actual_cmd->redir;
		while (current)
		{
			if (current->type == RD_HEREDOC
				&& create_heredoc(mini, current) == -1
				&& signal(SIGINT, signal_handler))
				return (-1);
			current = current->next;
		}
		actual_cmd = actual_cmd->next;
	}
	return (0);
}

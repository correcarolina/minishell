/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdblocks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:19:05 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/09 13:09:05 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_cmdblock *cmd, int prev_fd, int next_fd[2], t_ms *ms)
{
	int	status;

	status = 0;
	close_2_fds(ms->stdinout_copy[0], ms->stdinout_copy[1]);
	if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (cmd->next)
		dup2(next_fd[1], STDOUT_FILENO);
	close_fd(prev_fd);
	close_2_fds(next_fd[1], next_fd[0]);
	if (handle_redirection(cmd->redir, ms) == -1)
	{
		clean_cmdblocks_ms_and_history(ms);
		exit(1);
	}
	if (!cmd->cmd || !cmd->cmd[0])
	{
		ft_clear_cmdblock(&ms->cmdblocks);
		exit(EXIT_SUCCESS);
	}
	status = execute_single_command(cmd->cmd, ms);
	clean_cmdblocks_ms_and_history(ms);
	exit(status);
}

//takes the command block list and creates pipes between them (one pipe per
//command block if it is not the last one)
//it also forks a child for each command block
pid_t	create_pipes(t_cmdblock *cmdblock, t_ms *ms)
{
	int			pipe_fd[2];
	int			prev_fd;
	pid_t		pid;

	pid = 0;
	inizilize_3fds(&prev_fd, pipe_fd);
	while (cmdblock)
	{
		create_single_pipe(cmdblock, pipe_fd);
		signal(SIGINT, child_sighand);
		signal(SIGQUIT, child_sighand);
		pid = fork();
		if (pid == 0)
			child_process(cmdblock, prev_fd, pipe_fd, ms);
		close_fd(prev_fd);
		if (cmdblock->next)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		else
			close_fd(pipe_fd[0]);
		cmdblock = cmdblock->next;
	}
	return (close_fd(prev_fd), pid);
}

int	execute_cmdblocks(t_cmdblock *cmdblocks, t_ms *ms)
{
	int		ret;
	pid_t	last_pid;

	last_pid = -1;
	if (!cmdblocks || !cmdblocks->cmd || \
		(!cmdblocks->cmd[0] && !cmdblocks->redir))
		return (0);
	if (only_one_cmd(cmdblocks) && ft_strcmp(cmdblocks->cmd[0], "exit") == 0)
	{
		handle_redirection(cmdblocks->redir, ms);
		return (ft_exit(cmdblocks->cmd, ms, 1));
	}
	else if (only_one_cmd(cmdblocks) && is_built_in(cmdblocks->cmd[0]))
	{
		if (handle_redirection(cmdblocks->redir, ms) == -1)
			return (ms->exit_status);
		ret = execute_builtin(cmdblocks->cmd, ms);
		return (ret);
	}
	last_pid = create_pipes(cmdblocks, ms);
	ms->exit_status = wait_children(last_pid);
	return (ms->exit_status);
}

static int	handle_signal_exit(int status)
{
	int	sig;

	sig = WTERMSIG(status);
	return (128 + sig);
}

int	wait_children(pid_t last_pid)
{
	int		status;
	int		last_status;
	pid_t	pid;

	last_status = 0;
	pid = wait(&status);
	while (pid != -1)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = handle_signal_exit(status);
		}
		else if (WIFSIGNALED(status))
			handle_signal_exit(status);
		pid = wait(&status);
	}
	if (errno != ECHILD)
		perror("wait");
	g_signo = 0;
	return (last_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdblocks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:19:05 by cacorrea          #+#             */
/*   Updated: 2025/04/28 17:19:09 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_cmdblock *cmd, int prev_fd, int next_fd, t_ms *ms)
{
	if (prev_fd != -1)//non e il primo comando
		dup2(prev_fd, STDIN_FILENO);
	if (cmd->next)//non e l'ultimo comando
		dup2(next_fd, STDOUT_FILENO);
	close_fds(prev_fd, next_fd);
	if (handle_redirection(cmd->redir) == -1)
		exit(EXIT_FAILURE);
	//execve_wrapper(cmd->cmd, ms);or
	execute_single_command(cmd, prev_fd, -1, ms);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	create_pipes(t_cmdblock *cmdblock, t_ms *ms)
{
	int			pipe_fd[2];
	int			prev_fd = -1;
	pid_t		pid;

	while (cmdblock)
	{
		if (cmdblock->next && pipe(pipe_fd) == -1)//non e l'ultimo commando
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == 0)//child
			child_process(cmdblock, prev_fd, pipe_fd[1], ms);
		close_fds(prev_fd, -1);
		if (cmdblock->next)//non e l'ultimo commando
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		else
			close(prev_fd);
		cmdblock = cmdblock->next;
	}
}

int	execute_cmdblocks(t_cmdblock *cmdblocks, t_ms *ms)
{
	t_cmdblock	*current;

	current = cmdblocks;
	if (only_one_cmd(current) && is_built_in(current->cmd[0]))
	{
		execute_built_in_inparent(current, ms);
		return (0);
	}
	create_pipes(current, ms);
	ms->exit_status = wait_for_childs();
	return (ms->exit_status);
}

int	wait_for_childs(void)/*da aggiunggere qualcosa per segnali*/
{
	int status;     // Stores the exit status of child processes
	int	last_status; // Stores the last exit status
	pid_t pid;      // Stores the process ID of terminated children

	last_status = 0;
	pid = wait(&status);  // Wait for any child process to terminate
	while (pid > 0)  // Loop continues as long as there are children to wait for
	{
		if (WIFEXITED(status))                  // Child terminated normally
			last_status = WEXITSTATUS(status);       // Return the exit code (0-255)
		else if (WIFSIGNALED(status))           // Child terminated by a signal
			last_status = (128 + WTERMSIG(status));    // Return 128 + signal number
		pid = wait(&status);
	}
	if (pid == -1 && errno != ECHILD)  // Error checking
		perror("wait");
	return (-1);
}

/* Key Components:
Wait Loop:

wait(&status) suspends the parent process until a child terminates
Returns the PID of the terminated child
Stores the exit status in status
Status Checking:

WIFEXITED(status): Checks if child exited normally
WEXITSTATUS(status): Gets the exit code (0-255)
WIFSIGNALED(status): Checks if child was terminated by a signal
WTERMSIG(status): Gets the signal number that caused termination
Return Values:

Normal exit: Returns the child's exit code
Signal termination: Returns 128 + signal number (POSIX convention)
Error: Returns -1
Common Signal Return Examples:
SIGTERM (15): Returns 143 (128 + 15)
SIGKILL (9): Returns 137 (128 + 9)
SIGSEGV (11): Returns 139 (128 + 11) */
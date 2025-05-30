/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdblocks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:19:05 by cacorrea          #+#    #+#             */
/*   Updated: 2025/05/30 19:14:12 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void child_process(t_cmdblock *cmd, int prev_fd, int next_fd[2], t_ms *ms)
{
	int status;

	status = 0;
	close(ms->stdinout_copy[0]);
	close(ms->stdinout_copy[1]);
	setup_child_signals();
	if (prev_fd != -1)
		dup2(prev_fd, STDIN_FILENO);
	if (cmd->next)//non e l'ultimo comando
		dup2(next_fd[1], STDOUT_FILENO);
	close_fd(prev_fd);
	close_fd(next_fd[1]);
	close_fd(next_fd[0]);
	if (handle_redirection(cmd->redir) == -1)
	{
		ft_clear_cmdblock(&ms->cmdblocks);
		exit(EXIT_FAILURE);
	}
	if (!cmd->cmd || !cmd->cmd[0])
	{
		ft_clear_cmdblock(&ms->cmdblocks);
		exit(EXIT_SUCCESS);
	}
	status = execute_single_command(cmd->cmd, ms);
	ft_clear_cmdblock(&ms->cmdblocks);
	ms_cleanup(ms);
	free(ms);
	exit(status);
}


//takes the command block list and creates pipes between them (one pipe per
//command block if it is not the last one)
//it also forks a child for each command block
void	create_pipes(t_cmdblock *cmdblock, t_ms *ms)
{
	int			pipe_fd[2];
	int			prev_fd = -1;
	pid_t		pid;

	//inizializzo perche conditional jump
	pid = 0;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	while (cmdblock)
	{//se non e l'ultimo comando crea la pipe
		if (cmdblock->next && pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == 0)//child
			child_process(cmdblock, prev_fd, pipe_fd, ms);
		close_fd(prev_fd);
		if (cmdblock->next)//non e l'ultimo commando
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		else
			close_fd(pipe_fd[0]);
		cmdblock = cmdblock->next;
	}
	close_fd(prev_fd);
}

int execute_cmdblocks(t_cmdblock *cmdblocks, t_ms *ms)
{
    int ret;
    
	if (!cmdblocks || !cmdblocks->cmd || \
		(!cmdblocks->cmd[0] && !cmdblocks->redir))//se ci sono solo redir nella cmdblock bisogna arrivare a create_pipes
		return (0);//oppure return errore?
    if (only_one_cmd(cmdblocks) && is_built_in(cmdblocks->cmd[0]))
    {
        handle_redirection(cmdblocks->redir);
		ret = execute_builtin(cmdblocks->cmd, ms);
	//	ft_clear_cmdblock(&cmdblocks); //da invalid read
        return (ret);
    }
    create_pipes(cmdblocks, ms);
    ms->exit_status = wait_for_childs();
    return (ms->exit_status);
}

int wait_for_childs(void)
{
    int status;     // Stores the exit status of child processes
    int last_status; // Stores the last exit status
    pid_t pid;      // Stores the process ID of terminated children

    last_status = 0;
    pid = wait(&status);  // Wait for any child process to terminate
    while (pid > 0)  // Loop continues as long as there are children to wait for
    {
        if (WIFEXITED(status))  // Child terminated normally
            last_status = WEXITSTATUS(status);  // Return the exit code (0-255)
        else if (WIFSIGNALED(status))  // Child terminated by a signal
        {
            int sig = WTERMSIG(status);
            if (sig == SIGINT)
                write(STDERR_FILENO, "\n", 1);
            else if (sig == SIGQUIT)
                write(STDERR_FILENO, "Quit (core dumped)\n", 19);
            last_status = (128 + sig);
        }
        pid = wait(&status);
    }
    g_signo = 0;
    if (pid == -1 && errno != ECHILD)
        perror("wait");
    return (last_status);
}

/* 
old one: 
int	wait_for_childs(void) //da aggiunggere qualcosa per segnali
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
	return (last_status);
}
*/


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
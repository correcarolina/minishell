/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:52:50 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/08 18:36:01 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_signo;

static void	ft_hd_ctrld(char *delim)
{
	 
		write(STDERR_FILENO, "minishell: warning: here-document delimited ", 45);
		write(STDERR_FILENO, "by end-of-file (wanted `", 25);
		write(STDERR_FILENO, delim, ft_strlen(delim));
		write(STDERR_FILENO, "')\n", 3);
	
}

static int	handle_line(t_ms *mini, char **line, char *delim, int quoted_hd)
{
	char	*tmp;

	if (!line /* && !*line && g_signo != SIGINT */)
	{
		printf("___________>\n");
		ft_hd_ctrld(delim);
		return (0);
	}
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

static void	here_child(t_ms *mini, char *delimiter, int write_fd)
{
	char	*line;
	int		quoted_hd;
	int		res;

	signal(SIGINT, ft_hd_ctrlc);
	//setup_heredoc_signals();
	quoted_hd = ft_check_delimiter_quote(&delimiter);
	while (1)
	{
		// mini->exit_status = getsingal(mini);
		// if ( g_signo == SIGINT)
		// {
		// 	printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
		// 	exit(2);
		// }
		line = readline(AQUA "HEREDOC> " DEFAULT);
		// mini->exit_status = getsingal(mini);
		if (!line && g_signo != SIGINT)
		{
			mini->exit_status = getsingal(mini);
			write(1, "ctrlD\n", 6);
			printf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", delimiter);
			break ;
		}
		else if (!line && g_signo == SIGINT)
		{
			mini->exit_status = getsingal(mini);
			close_fd(write_fd);
			ft_clear_cmdblock(&mini->cmdblocks);
			ms_cleanup(mini);
			exit(130);
		}
		res = handle_line(mini, &line, delimiter, quoted_hd);
		if (res <= 0)
			break ;
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
		line = NULL;
	}
	close_fd(write_fd);
	ft_clear_cmdblock(&mini->cmdblocks);
	ms_cleanup(mini);
	exit(0);
}

static int	create_heredoc(t_ms *mini, t_redirlst *current)
{
	int		fd[2];
	pid_t	pid;

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
		//setup_child_signals(); // <--------------
		here_child(mini, current->content, fd[1]);
	}
	close(fd[1]);
	current->heredoc_fd = fd[0];
	return (ft_wait_heredoc(pid));
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

/* prima di eseguire i commandi:
scorrere la lista di comandi alla ricerca di << RD_HEREDOC
se li trova chiama una funzione che:
-crea una pipe
-fork
	nel child:close fd[0] read end
	chiama una funzione che gestisce il ciclo di readline HEREDOC ****
	fa l'espansione delle variabili

	nel parent: chiude fd[1] write end
	salva il fd[0] in redir->heredoc_fd


nell'esecuzione: quando arriva a un << 
fa la redirection con dup2(redir->heredoc_fd, STDIN_FILENO)
chiude la pipe fd[0] readend 

****funzione che gestisce il ciclo:
metti il controllo dei segnali
-while(1)
{
	-leggi la riga
	-se la riga e uguale al delimitatore esci
	-altrimenti espandi (anche $?) e scrivi nella pipe
	-printf("\n");
}

nel parsing il delimitatore del heredoc lo devi tenere cosi come:
$USER	non espandere
"EOF"	non levare le quotes ne single ne doubles

perche se il delimiter e fra virgolette "EOF" o 'EOF' non devi espandere
la linea che ricevi dal ciclo di input */
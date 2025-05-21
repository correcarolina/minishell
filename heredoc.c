/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:52:50 by cacorrea          #+#    #+#             */
/*   Updated: 2025/05/08 12:52:53 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_expand_heredoc(t_ms *mini, char **line)//non cosi
{
	char	*start;
	char	*expanded;
	char	*tmp;
	int		i;

	i = 0;
	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	start = *line;
	while (*start)
	{
		i = 0;
		while (start[i] && start[i] != '$')
			i++;
		tmp = ft_substr(start, 0, i);
		expanded = ft_strjoin_free(expanded, tmp);
		free(tmp);
		start += i;
		if (*start == '$')
		{
			start++;
			expanded = ft_get_expansion(*mini, &start, expanded);
		}
	}
	return (expanded);
}

static void	here_child(t_ms *mini, char *delimiter, int write_fd)
{
	char	*line;
	char	*tmp;
	int		quoted_hd;

	//gestire i segnali, se esce con ctrl+d stampare messaggio di warning
	quoted_hd = 0;
	if (delimiter && delimiter[0] == S_QUOTE && delimiter[1] != '\0')
	{
		quoted_hd = 1;
		delimiter++;
	}
	while (1)
	{
		line = readline(AQUA "HEREDOC> " DEFAULT);
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		if (ft_strchr(line, '$') && quoted_hd == 1)//da aggiungere non farlo se delimiter e fra virgolette
		{
			tmp = ft_expand_heredoc(mini, &line);//if (!tmp) free(line), break???;
			free(line);//se lungo questo check spostarlo in ft_expand_heredoc
			line = tmp;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close_fd(write_fd);
	exit(0);
}

static int	create_heredoc(t_ms	*mini, t_redirlst *current)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		close_fd(fd[0]);
		here_child(mini, current->content, fd[1]);
	}
	close(fd[1]);
	current->heredoc_fd = fd[0];
	waitpid(pid, NULL, 0);
	return (0);
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
			if (current->type == RD_HEREDOC)
			{
				if (create_heredoc(mini, current) == -1)
					return (-1);
			}
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
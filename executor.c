/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:08:07 by cacorrea          #+#    #+#             */
/*   Updated: 2025/05/12 18:33:38 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **cmd, t_ms *mini)//cosa restituiscono?
{
	int	status;

	status = 0;
	if (!cmd || !cmd[0])
	        return 0;
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		builtin_echo(cmd);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		status = ft_cd(cmd, mini);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		status = ft_pwd(mini);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		status = ft_export(cmd, mini);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		status = ft_unset(cmd, mini);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		status = ft_env(cmd, mini);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		return (ft_exit(cmd, mini));
	mini->exit_status = status;
	return (status);
}


int	execute_single_command(char **cmd, t_ms *mini)
{
	//char **env;
	printf("da fare l'esecutore :(\n");//execve_wrapper(cmd, mini);
	//env = envlist_to_matrix(mini->myenv);in exec_utils
	//if (access(cmd[0], F_OK) == 0)
	//altrimenti cercarsi il percorso nel PATH ---> ft_getenv_var gia esiste
	//splittare il path in una matrice di stringhe
	//char **path = ft_split(ft_getenv_var(mini, "PATH"), ':');
	//se non ce il '\' nel path, lo aggiungo
	//provare access con le stringe nella nuova matric finche non lo trova 
	//	execve(cmd[0], cmd, mini->envp);
	//se arriva qui vuole dire che c'e un errore con access al file o percorso e quindi fa pulizia e ritorna errore
	//free(path);
	//ms_cleanup(mini);
	//(perror("execve"); return (127);
}

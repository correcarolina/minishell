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
		ft_cd(cmd, mini);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		ft_pwd( mini);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		ft_export(cmd, mini);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		ft_unset(cmd, mini);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		ft_env(cmd, mini);
	else if (ft_strncmp(cmd[0], "exit", 4) == 0)
		return (ft_exit(cmd, mini));
	//exit (status)?;
	return (0);
}


int	execute_single_command(char **cmd, t_ms *mini)
{
	//char **env;
	printf("da fare l'esecutore :(\n");//execve_wrapper(cmd, mini);
	//env = envlist_to_matrix(mini->myenv);da fare in exec_utils
	//	execve(cmd[0], cmd, mini->envp);
	//ms_cleanup(mini);
	perror("execve");
	return (127);
}

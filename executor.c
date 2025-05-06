/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:08:07 by cacorrea          #+#    #+#             */
/*   Updated: 2025/05/06 19:38:45 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_single_command(char **cmd, t_ms *mini)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		builtin_echo(cmd);
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		ft_cd(cmd, mini);
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		ft_pwd(cmd, mini);
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		ft_export(cmd, mini);
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		ft_unset(cmd, mini);
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		ft_env(cmd, mini);
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
	{
		printf("exit\n");//o meglio da fare aparte
		exit(0);
	}
	else
		printf("da fare l'esecutore :(\n");//execve_wrapper(cmd, mini);
	return (0);
}

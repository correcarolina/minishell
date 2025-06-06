/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 19:09:32 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/06 11:03:33 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **cmd, t_ms *mini)
{
	int	status;

	status = 0;
	if (!cmd || !cmd[0])
		return (0);
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		status = builtin_echo(cmd);
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
		return (ft_exit(cmd, mini, 0));
	mini->exit_status = status;
	return (status);
}

int	is_built_in(char *cmd)
{
	if (ft_strncmp(cmd, "exit", 5) == 0 || \
		ft_strncmp(cmd, "echo", 5) == 0 || \
		ft_strncmp(cmd, "cd", 3) == 0 || \
		ft_strncmp(cmd, "pwd", 4) == 0 || \
		ft_strncmp(cmd, "export", 7) == 0 || \
		ft_strncmp(cmd, "unset", 6) == 0 || \
		ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	return (0);
}

void	print_builtin_error(char *builtin, char *arg, t_ms *mini)
{
	mini->exit_status = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(builtin, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

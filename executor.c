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
	        return (0);
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


static char	*get_path(char *cmd, char *envpath)
{
	char	*initial_path;
	char	*cmd_path;
	char	**path_array;
	int		i;

	i = 0;
	if (envpath == NULL)
		return (NULL);
	path_array = ft_split(envpath, ':');
	while (path_array[i] != NULL)
	{
		initial_path = ft_strjoin(path_array[i], "/");
		cmd_path = ft_strjoin(initial_path, cmd);
		free(initial_path);
		if (access(cmd_path, X_OK) == 0)
		{
			ft_free_matrix(path_array);
			return (cmd_path);
		}	
		free(cmd_path);
		i++;
	}
	ft_free_matrix(path_array);
	return (NULL);
}


int	execute_single_command(char **cmd, t_ms *mini)
{
	char **env;
	char *cmd_path;

	if (is_built_in(cmd[0]))
		return (execute_builtin(cmd, mini));
	env = envlst_to_matrix(mini->myenv);
	if (access(cmd[0], X_OK) == 0)
	{
		execve(cmd[0], cmd, env);
		free(env);
		return (0);
	}
	cmd_path = get_path(cmd[0], ft_getenv_var(mini, "PATH"));
	if (!cmd_path)
	{
		ft_error_print(cmd[0], mini, 1);
		free(env);
		return (127);
	}
	execve(cmd_path, cmd, env);
	free(cmd_path);
	free(env);
	mini->exit_status = 126;
	return (perror("execve"), 127);
}

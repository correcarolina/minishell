/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:08:07 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/05 13:12:12 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//searchs into env PATH and returns the command path if found
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

static int	try_exec_path(char **cmd, char **env, t_ms *mini)
{
	execve(cmd[0], cmd, env);
	if (errno == EACCES)
		ft_print_error(cmd[0], mini, 4); // Permission denied
	else if (errno == ENOENT)
		ft_print_error(cmd[0], mini, 3); // No such file or directory
	else if (errno == ENOTDIR)
		ft_print_error2(cmd[0], mini, 5); // Not a directory
	else
	{
		perror("execve");
		mini->exit_status = 126;
	}
	return (mini->exit_status);
}

static int	missing_path(char **cmd, char **env, t_ms *mini)
{
	int	status;

	status = try_exec_path(cmd, env, mini);
	ft_free_matrix(env);
	return (status);
}

static int	execute_in_path(char **cmd, char **env, t_ms *mini)
{
	char	*cmd_path;
	char	*path_env;

	if (cmd[0] && cmd[0][0] == '\0')
	{
		ft_print_error("''", mini, 1);//command not found
		ft_free_matrix(env);
		return (mini->exit_status);
	}
	path_env = ft_getenv_var(mini, "PATH");
	if (!path_env || path_env[0] == '\0')
		return (missing_path(cmd, env, mini));
	cmd_path = get_path(cmd[0], path_env);
	free(path_env);
	if (!cmd_path)
		return (cmd_not_found(cmd[0], env, mini, cmd_path));
	execve(cmd_path, cmd, env);
	perror("execve");
	free(cmd_path);
	ft_free_matrix(env);
	mini->exit_status = 126;
	return (126);
}

int	execute_single_command(char **cmd, t_ms *mini)
{
	char	**env;
	int		status;

	status = 0;
	if (is_built_in(cmd[0]))
		return (execute_builtin(cmd, mini));
	env = envlst_to_matrix(mini->myenv);
	if (access(cmd[0], X_OK) == 0)
	{
		execve(cmd[0], cmd, env);
		perror("execve");
		ft_free_matrix(env);
		mini->exit_status = 126;
		return (126);
	}
	if (ft_strchr(cmd[0], '/'))
	{
		status = try_exec_path(cmd, env, mini);
		ft_free_matrix(env);
		return (status);
	}
	return (execute_in_path(cmd, env, mini));
}


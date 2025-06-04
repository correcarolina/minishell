/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:08:07 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/04 13:52:50 by cacorrea         ###   ########.fr       */
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
			free(envpath);
			ft_free_matrix(path_array);
			return (cmd_path);
		}	
		free(cmd_path);
		i++;
	}
	ft_free_matrix(path_array);
	return (free(envpath), NULL);
}

static int	execute_in_path(char **cmd, char **env, t_ms *mini)
{
	char	*cmd_path;

	if (cmd[0] && cmd[0][0] == '\0')
	{
		ft_putendl_fd("\'\': command not found", 2);
		ft_free_matrix(env);
		return (127);
	}
	cmd_path = get_path(cmd[0], ft_getenv_var(mini, "PATH"));
	if (!cmd_path)
	 {
		ft_print_error(cmd[0], mini, 1);//command not found
		ft_free_matrix(env);
		return (127);
	}
	execve(cmd_path, cmd, env);
	perror("execve");
	free(cmd_path);
	ft_free_matrix(env);
	return (126);
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
		perror("execve");
	return (mini->exit_status);
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

void	create_single_pipe(t_cmdblock *cmd, int pipe_fd[2])
{
	if (cmd->next && pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}


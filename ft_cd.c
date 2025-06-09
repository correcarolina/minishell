/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:57:08 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/09 19:06:36 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Updates PWD and OLDPWD environment variables after changing directory
 * @param mini Pointer to the shell structure
 * @param cwd New current working directory
 * @param owd Previous working directory
 */
static void	update_pwd_vars(t_ms *mini, char *cwd, char *owd)
{
	t_envlst	*pwd_node;
	t_envlst	*oldpwd_node;
	char		*temp;

	temp = NULL;
	pwd_node = env_get_node(&mini->myenv, "PWD");
	oldpwd_node = env_get_node(&mini->myenv, "OLDPWD");
	if (pwd_node)
	{
		free(pwd_node->value);
		pwd_node->value = ft_strdup(cwd);
	}
	if (oldpwd_node)
	{
		free(oldpwd_node->value);
		oldpwd_node->value = ft_strdup(owd);
	}
	else if (!oldpwd_node)
	{
		temp = ft_strjoin("OLDPWD=", owd);
		env_append_node(&mini->myenv, env_new_node(temp));
		free (temp);
	}
}

/**
 * Gets home directory from environment variables
 * @param mini Pointer to the shell structure
 * @return Home directory path or NULL if not found
 */
static char	*get_home_dir(t_ms *mini)
{
	t_envlst	*home_node;

	home_node = mini->myenv;
	while (home_node)
	{
		if (ft_strcmp(home_node->key, "HOME") == 0)
			return (home_node->value);
		home_node = home_node->next;
	}
	return (NULL);
}

static char	*get_target_directory(char **cmd, t_ms *mini)
{
	char	*target_dir;

	if (cmd[1] == NULL)
	{
		target_dir = get_home_dir(mini);
		if (!target_dir)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			mini->exit_status = 1;
			return (NULL);
		}
	}
	else if (cmd[1] && strcmp(cmd[1], "-") == 0)
	{
		target_dir = ft_getenv_var(mini, "OLDPWD");
		if (!target_dir)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			mini->exit_status = 1;
			return (NULL);
		}
	}
	else
		target_dir = cmd[1];
	return (target_dir);
}

static int	perform_cd(char *target_dir, t_ms *mini, char *old_dir)
{
	char	cwd[4096];

	if (chdir(target_dir) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(target_dir, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		mini->exit_status = 1;
		return (1);
	}	
	if (getcwd(cwd, 4096) == NULL)
		return (ft_putstr_fd("minishell: cd: getcwd error\n", 2), 1);
	update_pwd_vars(mini, cwd, old_dir);
	if (mini->cwd)
		free(mini->cwd);
	mini->cwd = ft_strdup(cwd);
	if (!mini->cwd)
	{
		ft_putstr_fd("cd: memory allocation error\n", 2);
		return (mini->exit_status = 1, 1);
	}
	return (0);
}

int	ft_cd(char **cmd, t_ms *mini)
{
	char	owd[4096];
	char	*target_dir;

	if (getcwd(owd, 4096) == NULL)
		return (ft_putstr_fd("minishell: cd: getcwd error\n", 2), 1);
	target_dir = get_target_directory(cmd, mini);
	if (!target_dir)
		return (1);
	if (perform_cd(target_dir, mini, owd))
		return (1);
	mini->exit_status = 0;
	return (0);
}

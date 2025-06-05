/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:18:20 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/05 20:17:06 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_not_found(char *cmd_name, char **env, t_ms *mini, char *cmd_path)
{
	ft_print_error(cmd_name, mini, 1);
	ft_free_matrix(env);
	free(cmd_path);
	return (mini->exit_status);
}

int	only_one_cmd(t_cmdblock *cmdblocks)
{
	t_cmdblock	*current;

	current = cmdblocks;
	if (current->next == NULL)
		return (1);
	return (0);
}

//Duplicates the given key and value, joins them with an '=' character,
//and returns the resulting string (e.g., "KEY=VALUE").
static char	*dup_key_value(char *key, char *value)
{
	char	*result;
	char	*dup_key;
	char	*dup_value;

	result = NULL;
	dup_key = ft_strdup(key);
	dup_value = ft_strdup(value);
	if (!dup_key || !dup_value)
	{
		free(dup_key);
		free(dup_value);
		return (NULL);
	}
	result = ft_strjoin_3(dup_key, "=", dup_value);
	free(dup_key);
	free(dup_value);
	return (result);
}

//takes the env list and creates a matrix of strings to pass to execve
char	**envlst_to_matrix(t_envlst *env)
{
	char		**matrix;
	int			i;

	matrix = (char **)malloc(sizeof(char *) * (ft_lstsize(env) + 1));
	if (!matrix)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value == NULL)
			matrix[i] = ft_strjoin(env->key, "=");
		else
			matrix[i] = dup_key_value(env->key, env->value);
		if (!matrix[i])
		{
			free_matrix(matrix, i - 1);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	matrix[i] = NULL;
	return (matrix);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 23:26:00 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/03 13:42:51 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initialize and allocate the main minishell structure (t_mini).
// Copies environment variables, retrieves PWD, and duplicates stdin/stdout.
// Returns a pointer to the initialized structure or NULL on failure.

t_ms	*ft_init(char **env)
{
	t_ms		*mini;

	mini = (t_ms *)malloc(sizeof(t_ms));
	if (!mini)
		return (NULL);
	mini->cmdblocks = NULL;
	mini->myenv = ft_env_cpy(NULL, env);
	if (!mini->myenv)
	{
		free(mini);
		return (NULL);
	}
	mini->cwd = ft_getenv_var(mini, "PWD");
	mini->stdinout_copy[0] = dup(STDIN_FILENO);
	mini->stdinout_copy[1] = dup(STDOUT_FILENO);
	if (mini->stdinout_copy[0] == -1 || mini->stdinout_copy[1] == -1)
	{
		perror("dup");
		ms_cleanup(mini);
		return (NULL);
	}
	mini->exit_status = 0;
	return (mini);
}

// Clean up the minishell structure (t_ms).
// Frees memory, clears environment list, restores stdin/stdout, and closes fds
void	ms_cleanup(t_ms *mini)
{
	if (mini->cwd)
		free(mini->cwd);
	if (mini->myenv)
		env_clear_lst(&mini->myenv);
	dup2(mini->stdinout_copy[0], STDIN_FILENO);
	dup2(mini->stdinout_copy[1], STDOUT_FILENO);
	close_fd(mini->stdinout_copy[0]);
	close_fd(mini->stdinout_copy[1]);
	mini->stdinout_copy[0] = -1;
	mini->stdinout_copy[1] = -1;
	free(mini);
}

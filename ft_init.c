/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 23:26:00 by cacorrea          #+#    #+#             */
/*   Updated: 2025/05/31 23:40:15 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

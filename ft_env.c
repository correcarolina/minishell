/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:40:24 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/03 13:41:06 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Prints the current environment variables in the standard "key=value" format
int	ft_env(char **cmd, t_ms	*mini)
{
	t_envlst	*temp;

	temp = mini->myenv;
	if (cmd[1] != NULL)
	{
		printf("env: %s: No such file or directory\n", cmd[1]);
		mini->exit_status = 127;
		return (127);
	}
	while (temp)
	{
		if (temp->value)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	mini->exit_status = 0;
	return (0);
}

//Prints the environment variables in a format used by the `export` built-in
void	env_export_print(t_envlst *env)
{
	t_envlst	*temp;

	temp = env;
	while (temp)
	{
		if (!temp->value)
			printf("declare -x %s\n", temp->key);
		else
			printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
		temp = temp->next;
	}
}

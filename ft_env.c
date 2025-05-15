/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 11:40:24 by cacorrea          #+#    #+#             */
/*   Updated: 2025/02/08 11:40:27 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **cmd, t_ms	*mini)//e il cmd
{
	t_envlst	*temp;

	temp = mini->myenv;
	if(cmd[1] != NULL)
	{
		printf("env: %s: No such file or directory\n", cmd[1]);
		mini->exit_status = 127;
		return (127);
	}
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	mini->exit_status = 0;
	return (0);
}

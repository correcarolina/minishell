/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:39:58 by cacorrea          #+#    #+#             */
/*   Updated: 2025/02/10 10:40:04 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Searches for the given environment variable in my t_ms struct and returns 
//its value as a newly allocated string. 
//If the variable is not found, prints an error message and returns NULL.

char	*ft_getenv_var(t_ms *mini, char *name)
{
	t_envlst	*temp;

	if (!mini || !mini->myenv || !name)
		return (NULL);
	temp = mini->myenv;
	while (temp)
	{
		if (ft_strncmp(name, temp->key, ft_strlen(name) + 1) == 0)
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (NULL);
}

//gets the working directory from the env var in my t_ms struct and prints it.

void	ft_pwd(char **cmd, t_ms *mini)
{
	char *actual_dir;

	if (!mini)
		return;
	actual_dir = mini->cwd;
	if (!actual_dir)
	{
		mini->exit_status = EXIT_FAILURE;
		return;
	}	
	printf("%s\n", actual_dir);
	mini->exit_status = EXIT_SUCCESS;
	free(actual_dir);
}


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

void	ft_env(t_ms	*mini)//e il cmd
{
	//controllare che il numero di arg sia == 1 (env senza argomenti)solo il cmd
	//cosa li passo?: 	una str: env ciao carolina
	//					una matrice:	env'\0'
	//									ciao'\0'
	//									carolina'\0'
	//					o una lista: 	env'\0' -->  ciao'\0' -->  carolina'\0'
	//se ci sono flags o args manda error msg
	t_envlst	*temp;

	temp = mini->myenv;
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
}

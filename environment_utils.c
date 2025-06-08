/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 10:30:55 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/08 21:45:27 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//functions for handling the list of environement
//function to clear one node
void	env_clear_node(t_envlst *node)
{
	if (!node)
		return ;
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

//function to clear the list
void	env_clear_lst(t_envlst **head)
{
	t_envlst	*temp;

	if (!head || !*head)
		return ;
	while (*head != NULL)
	{
		temp = (*head)->next;
		free((*head)->key);
		if ((*head)->value)
			free((*head)->value);
		free(*head);
		*head = temp;
	}
}

//copies a matrix into a linked list
t_envlst	*ft_env_cpy(t_envlst *myenv, char **matrix)
{
	int			j;
	t_envlst	*new;

	j = 0;
	myenv = NULL;
	while (matrix[j] != NULL)
	{
		new = env_new_node(matrix[j]);
		if (!new)
		{
			env_clear_lst(&myenv);
			return (NULL);
		}
		env_append_node(&myenv, new);
		j++;
	}
	return (myenv);
}

//function to get the size of the list
int	ft_lstsize(t_envlst *lst)
{
	int			i;
	t_envlst	*ptr;

	i = 0;
	ptr = lst;
	while (ptr != NULL)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}

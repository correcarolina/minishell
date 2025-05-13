/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:17:03 by cacorrea          #+#    #+#             */
/*   Updated: 2025/02/07 17:17:10 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/********************funziona e non ha leaks*********************/

//creates a new node and puts an environment variable into two separates strings

t_envlst	*env_new_node(char *var)
{
	t_envlst		*new;
	size_t			i;

	i = 0;
	new = (t_envlst *)malloc(sizeof(t_envlst));
	if (!new)
		return (NULL);
	while (var[i] != '\0' && var[i] != '=')
		i++;
	new->key = ft_substr(var, 0, i);
	if (!new->key)
	{
		free(new);
		return (NULL);
	}
	if (i == ft_strlen(var))//se non c'e '='
	{
		new->value = (char *)ft_calloc(1, sizeof(char));
		if (!new->value)
			new->value = NULL;
	}
	else
		new->value = ft_strdup((var + i + 1));//devo controllare errore di malloc
	new->next = NULL;//e liberare il nodo?
	return (new);
}

/*Adds the node ’new’ at the end of the list.
	lst: The address of a pointer to the head of a list.
	new: The address of a pointer to the node to be added to the list.*/

void	env_append_node(t_envlst **lst, t_envlst *new)
{
	t_envlst	*last;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next != NULL)
		{
			last = last->next;
		}
		last->next = new;
	}
}

//function to clear one node

void	env_clear_node(t_envlst *node)
{
	if (!node)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

//function that clears the list

void	env_clear_lst(t_envlst **head)
{
	t_envlst	*temp;

	if (!head || !*head)
		return ;
	while (*head != NULL)
	{
		temp = (*head)->next;
		free((*head)->key);
		free((*head)->value);
		free(*head);
		*head = temp;
	}
}

//removes a node from the environment list by key. 
//@str: the key to be removed
//if key is found, the node is removed and the memory is freeded, 
//if not found, the list remains unchanged

void	env_rm_node(t_envlst **head, char *str)
{
	t_envlst	*temp;
	t_envlst	*prev;

	if (!head || !*head || !str)
		return ;
	temp = *head;
	if (ft_strncmp(str, temp->key, ft_strlen(str) + 1) == 0)
	{
		(*head) = (*head)->next;
		env_clear_node(temp);
		return ;
	}
	prev = temp;
	temp = temp->next;
	while (temp != NULL)
	{
		if (ft_strncmp(str, temp->key, ft_strlen(str) + 1) == 0)
		{
			prev->next = temp->next;
			env_clear_node(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
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

int	ft_lstsize(t_envlst *lst)
{
	int		i;
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
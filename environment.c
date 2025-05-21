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
//the key is the string before the '=' and the value is the string after the '='
//if there is no '=', the value is NULL, 
//if there is the '=' but no value, the value is an empty string
//returns the new node
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
		new->value = NULL;
	else
		new->value = ft_strdup((var + i + 1));
	new->next = NULL;
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

//function to get the node by key
//returns the node if found, NULL if not found
//if the list is empty, or the key is NULL, returns NULL
t_envlst	*env_get_node(t_envlst **head, char *key)
{
	t_envlst	*temp;

	if (!head || !*head || !key)
		return (NULL);
	temp = *head;
	while (temp != NULL)
	{
		if (ft_strncmp(key, temp->key, ft_strlen(key) + 1) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

//Searches for the given environment variable in my t_ms struct and returns 
//its value as a newly allocated string. 
//If the variable is not found, prints an error message and returns NULL.

char	*ft_getenv_var(t_ms *mini, char *name)
{
	t_envlst	*temp;
	char		*value;

	value = NULL;
	if (!mini || !mini->myenv || !name)
		return (NULL);
	temp = mini->myenv;
	while (temp)
	{
		if (ft_strncmp(name, temp->key, ft_strlen(name) + 1) == 0)
		{
			if (temp->value == NULL)
				return (NULL);
			value = ft_strdup(temp->value);
			if (!value)
			{
				perror("malloc");
				return (NULL);
			}
			return (value);
		}
		temp = temp->next;
	}
	return (NULL);
}

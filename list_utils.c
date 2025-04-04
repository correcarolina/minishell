/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:13:04 by cacorrea          #+#    #+#             */
/*   Updated: 2025/02/01 18:13:12 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//creates a new node and puts a string in the content

t_list	*ft_lstnew(char *content)
{
	t_list	*new;
	int		i;

	i = 0;
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->type = 0;
	new->next = NULL;
	return (new);
}

/*Adds the node ’new’ at the end of the list.
	@lst: The address of a pointer to the head of a list.
	@new: The address of a pointer to the node to be added to the list.*/

void	ft_append_node(t_list **lst, t_list *new_node)
{
	t_list	*last;

	if (!lst || !new_node)
		return ;
	if (!*lst)
		*lst = new_node;
	else
	{
		last = *lst;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
}

//function that clears the list

void	ft_clear_lst(t_list **head)
{
	t_list	*temp;

	temp = NULL;
	if (*head == NULL)
		return ;
	while (*head != NULL)
	{
		temp = (*head)->next;
		free((*head)->content);
		free(*head);
		*head = temp;
	}
}

/*Returns the last node of the list.*/

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	ptr = lst;
	if (lst == NULL)
		return (NULL);
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	return (ptr);
}

//fn per stampare la lista per debbuging ************************da levare
void print_input(t_list *lista)
{
	int	i;

	i = 0;
	while (lista)
	{
		printf("%i: Value: %s, \ttype: %d\n", i, lista->content, (lista->type));
		lista = lista->next;
		i++;
	}
}

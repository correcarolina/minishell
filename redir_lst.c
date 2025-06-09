/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:04:52 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/09 13:12:26 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//creates a new node and puts a string in the content and a type in the type
//this is used for the redirections in the cmdblock list
t_redirlst	*ft_redir_lstnew(char *content, int type)
{
	t_redirlst	*new;
	int			i;

	i = 0;
	new = (t_redirlst *)malloc(sizeof(t_redirlst));
	if (!new)
		return (NULL);
	new->content = ft_strdup(content);
	if (!new->content)
	{
		free(new);
		return (NULL);
	}
	new->type = type;
	new->heredoc_fd = -1;
	new->next = NULL;
	return (new);
}

void	ft_redir_append_node(t_redirlst **lst, t_redirlst *new_node)
{
	t_redirlst	*last;

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

void	ft_redir_clear_lst(t_redirlst **head)
{
	t_redirlst	*temp;

	temp = NULL;
	if (!head || !*head)
		return ;
	while (*head != NULL)
	{
		temp = (*head)->next;
		free((*head)->content);
		close_fd((*head)->heredoc_fd);
		free(*head);
		*head = temp;
	}
}

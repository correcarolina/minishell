/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:10:29 by cacorrea          #+#    #+#             */
/*   Updated: 2025/04/23 18:10:33 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmdblock	*ft_new_cmdblock(char **cmd, t_list *redir)
{
	t_cmdblock	*new;
	int			i;

	i = 0;
	new = (t_cmdblock *)malloc(sizeof(t_cmdblock));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->redir = redir;
	new->next = NULL;
	return (new);
}

//adds the node ’new’ at the end of the list.
void	ft_append_cmdblock(t_cmdblock **lst, t_cmdblock *new_node)
{
	t_cmdblock	*last;

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

//clear the list
void	ft_clear_cmdblock(t_cmdblock **head)
{
	t_cmdblock	*tmp;

	if (!head || !*head)
		return ;
	while (*head != NULL)
	{
		tmp = (*head)->next;
		ft_free_matrix((*head)->cmd);
		ft_clear_lst(&((*head)->redir));
		free(*head);
		*head = tmp;
	}
}

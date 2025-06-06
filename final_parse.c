/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:36:39 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/06 17:42:00 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_cmd_size(t_list *line)
{
	t_list	*current;
	int		i;

	i = 0;
	current = line;
	while (current && current->type != PIPE)
	{
		if (current->type == CMD || current->type == ARG)
			i++;
		current = current->next;
	}
	return (i);
}

void	free_matrix(char **matrix, int i)
{
	while (i >= 0)
	{
		free(matrix[i]);
		i--;
	}
	free(matrix);
}

//This function takes a linked list of tokens and creates a matrix of strings
//That represents the command and its arguments.
char	**ft_cmd_matrix(t_list *line)
{
	t_list		*current;
	char		**matrix;
	int			i;

	current = line;
	i = ft_cmd_size(line);
	if (i == 0)
		return (NULL);
	matrix = (char **)malloc(sizeof(char *) * (i + 1));
	if (!matrix)
		return (NULL);
	matrix[i] = NULL;
	i = 0;
	while (current && current->type != PIPE)
	{
		if (current->type == CMD || current->type == ARG)
		{
			matrix[i] = ft_strdup(current->content);
			if (!matrix[i])
				return (free_matrix(matrix, i - 1), NULL);
			i++;
		}
		current = current->next;
	}
	return (matrix);
}

//This function takes a linked list of tokens and creates a linked list of
//redirections. Each node contains the file name and the redirection type
t_redirlst	*redir_lst(t_list *line)
{
	t_redirlst	*redir;
	t_list		*current;

	current = line;
	redir = NULL;
	while (current && current->type != PIPE)
	{
		if (current->type == RD_IN || current->type == RD_OUT_T \
		|| current->type == RD_OUT_A || current->type == RD_HEREDOC)
		{
			ft_redir_append_node(&redir, \
				ft_redir_lstnew(current->next->content, current->type));
		}
		current = current->next;
	}
	return (redir);
}

t_cmdblock	*ft_create_cmdblock(t_list *line)
{
	t_cmdblock	*cmdblock;
	t_cmdblock	*new;
	t_list		*start;

	cmdblock = NULL;
	start = line;
	while (start && start->type != PIPE)
	{
		new = ft_new_cmdblock(ft_cmd_matrix(start), redir_lst(start));
		if (!new)
		{
			ft_clear_cmdblock(&cmdblock);
			return (NULL);
		}
		ft_append_cmdblock(&cmdblock, new);
		while (start && start->type != PIPE)
			start = start->next;
		if (start && start->type == PIPE)
			start = start->next;
	}
	return (cmdblock);
}

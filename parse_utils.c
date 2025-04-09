/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:15:27 by cacorrea          #+#    #+#             */
/*   Updated: 2025/03/12 19:15:30 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//This functions iterate through the linked list of tokens and assign a type 

//qui nella strncmp includo anche il terminatore \0 per non assegnare uno di questi operatori
//a un token che non è un operatore ma in quotes es: "| grep "
void	ft_assign_operator(t_list *line)
{
	t_list	*current;

	current = line;
	while (current != NULL)
	{
		if (current->type == 0)
		{
			if (ft_strncmp(current->content, "|", 2) == 0)
				current->type = PIPE;
			else if (ft_strncmp(current->content, ">>", 3) == 0)
				current->type = RD_OUT_A;
			else if (ft_strncmp(current->content, ">", 2) == 0)
				current->type = RD_OUT_T;
			else if (ft_strncmp(current->content, "<<", 3) == 0)
				current->type = RD_HEREDOC;
			else if (ft_strncmp(current->content, "<", 2) == 0)
				current->type = RD_IN;
		}
		current = current->next;
	}
}

static int	ft_set_file_type(int redir_type)
{
	if (redir_type == RD_IN)
		return (INFILE);
	if (redir_type == RD_OUT_A)
		return (OUTFILE_A);
	if (redir_type == RD_OUT_T)
		return (OUTFILE_T);
	return (0);
}

void	ft_assign_file(t_list *line)
{
	t_list	*current;
	int		redir_type;

	current = line;
	while (current)
	{
		if (current->next && (current->type == RD_IN || \
			current->type == RD_OUT_T || current->type == RD_OUT_A))
		{
			redir_type = current->type;
			current = current->next;
			if (current->type == 0)
				current->type = ft_set_file_type(redir_type);
			else
			{
				ft_putstr_fd("Error: syntax error near unexpected token👻\n", 2);
				return ;
			}
		}
		current = current->next;
	}
}

void	ft_assign_delimiter(t_list *line)
{
	t_list	*current;

	current = line;
	while (current)
	{
		if (current->type == RD_HEREDOC && current->next)
		{
			current = current->next;
			if (current->type == 0)
				current->type = DELIMITER;
			else
			{
				ft_putstr_fd("Error: syntax error near unexpected token😈\n", 2);
				return ;
			}
		}
		current = current->next;
	}
}

void	ft_assign_cmd(t_list *line)
{
	t_list	*current;

	current = line;
	while (current != NULL)
	{
		if (current->type == ARG)
			current->type = 0;
		current = current->next;
	}
	current = line;
	while (current != NULL)
	{
		if (current->type == 0)
		{
			current->type = CMD;
			current = current->next;
			while (current != NULL && current->type == 0)
			{
				current->type = ARG;
				current = current->next;
			}
		}
		if (current != NULL)
			current = current->next;
	}
}

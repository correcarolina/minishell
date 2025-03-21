/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:10:18 by cacorrea          #+#    #+#             */
/*   Updated: 2025/03/01 18:10:21 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//This function iterates through the linked list of tokens and assigns a type 
//command

/* static void	ft_assign_cmd(t_list *line)
{
	t_list	*current;

	current = line;
	if (current->type == 0)
		current->type = CMD;
	current = current->next;
	while (current != NULL)
	{
		if (current->next != NULL && current->type != 0 && current->type != CMD)
			current = current->next;
		if (current->type == 0)
			current->type = CMD;
		else
		{
			ft_putstr_fd("Error: syntax error near unexpected token\n", 2);
			return ;
		}	
		current = current->next;
	}
}

static void	ft_assign_args(t_list *line)
{
	t_list	*current;

	current = line;
	while (current)
	{
		while (current->next && current->type != CMD)
			current = current->next;
		if (current->type == CMD && current->next)
		{
			current = current->next;
			while (current && current->type == 0)
			{
				current->type = ARG;
				current = current->next;
			}
		}
	}
} */

void	ft_parse(t_list *line)
{
	ft_assign_operator(line);
	ft_assign_delimiter(line);
	/*ft_assign_file(line);
	ft_assign_cmd(line);
	ft_assign_args(line); */
	//se rimane qualcosa senza assegnazione, assegnarli command  ?giusto?
}

void	debug_printer(t_list *line)
{
	t_list	*current;
	char	*token_type;

	current = line;
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	while (current)
	{
		if (current->type == 1)
			token_type = "PIPE";
		else if (current->type == 2)
			token_type = "RD_IN";
		else if (current->type == 3)
			token_type = "RD_OUT_T";
		else if (current->type == 4)
			token_type = "RD_OUT_A";
		else if (current->type == 5)
			token_type = "HEREDOC delimiter";
		else if (current->type == 6)
			token_type = "CMD";
		else if (current->type == 7)
			token_type = "ARG";
		else if (current->type == 8)
			token_type = "INFILE";
		else if (current->type == 9)
			token_type = "OUTFILE_T";
		else if (current->type == 10)
			token_type = "OUTFILE_A";
		else
			token_type = "type not assigned";
		printf("%s		type: %s\n", current->content, token_type);
		current = current->next;
	}
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

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

//if the first or last token is a pipe or if there are two pipes in a row or if
//a pipe is followed by a redirection or if a redirection is followed by a pipe
int	ft_check_pipes(t_list *line)
{
	t_list	*current;

	current = line;
	if (current->type == PIPE)
		return (ft_putstr_fd("syntax error near unexpected token '|'\n", 2), 0);
	while (current)
	{
		if (current->type == PIPE)
		{
			if (current->next == NULL || current->next->type == RD_HEREDOC || \
			current->next->type == PIPE || current->next->type == RD_IN || \
			current->next->type == RD_OUT_A || current->next->type == RD_OUT_T)
				return (ft_putstr_fd("syntax error near unexpected \
token '|'\n", 2), 0);
		}
		else if (current->type == RD_IN || current->type == RD_OUT_T \
		|| current->type == RD_OUT_A || current->type == RD_HEREDOC)
		{
			if (current->next == NULL || current->next->type == PIPE)
				return (ft_putstr_fd("syntax error near unexpected \
token \n", 2), 0);
		}
		current = current->next;
	}
	return (1);
}

//This function iterates through the linked list of tokens and assigns a type:
//command and arguments, operator, delimiter or file
void	ft_parse(t_list *line)
{
	ft_assign_operator(line);
	if (!ft_check_pipes(line))
		return ;
	ft_assign_delimiter(line);
	ft_assign_file(line);
	ft_assign_cmd(line);
	debug_printer(line);/********* da levare ************/	
}

//This function is a helper to debug the parser.
//Add "debug_printer(line);" in ft_parse() after ft_assign_cmd to see the output
//of the parser.
void	debug_printer(t_list *line)/********* da levare ************/
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
			token_type = "HEREDOC";
		else if (current->type == 6)
			token_type = "CMD";
		else if (current->type == 7)
			token_type = "ARG";
		else if (current->type == 8)
			token_type = "DELIMITER";
		else if (current->type == 9)
			token_type = "INFILE";
		else if (current->type == 10)
			token_type = "OUTFILE_T";
		else if (current->type == 11)
			token_type = "OUTFILE_A";
		else
			token_type = "type not assigned";
		printf("%-15s type: %-10s\n", current->content, token_type);
		current = current->next;
	}
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

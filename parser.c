/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 18:10:18 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/09 15:16:13 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if the first or last token is a pipe or if there are two pipes in a row or if
//a redirection is followed by a pipe
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
			if (current->next == NULL || current->next->type == PIPE)
				return (ft_putstr_fd("syntax error near unexpected \
token '|'\n", 2), 0);
		}
		else if (current->type == RD_IN || current->type == RD_OUT_T \
		|| current->type == RD_OUT_A || current->type == RD_HEREDOC)
		{
			if (current->next == NULL || current->next->type == PIPE)
				return (ft_putstr_fd("syntax error near unexpected \
token\n", 2), 0);
		}
		current = current->next;
	}
	return (1);
}

//This function iterates through the linked list of tokens and assigns a type:
//command and arguments, operator, delimiter or file
int	ft_parse(t_list *line)
{
	ft_assign_operator(line);
	if (!ft_check_pipes(line))
		return (-1);
	if (ft_assign_delimiter(line) == 1)
		return (-1);
	if (ft_assign_file(line) == 1)
		return (-1);
	ft_assign_cmd(line);
	return (0);
}

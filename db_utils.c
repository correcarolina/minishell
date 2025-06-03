/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:04:01 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/03 12:24:51 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printcommand(t_cmdblock *head)
{
	t_cmdblock	*tmp;
	t_redirlst	*redir;
	int			j;
	char		*str;
	int			i;

	tmp = head;
	while (tmp)
	{
		i = 0;
		
		while (tmp->cmd[i])
		{
			printf("%d: %s\n", i, tmp->cmd[i]);
			i++;
		}
		redir = tmp->redir;
		j = 0;
		while (redir)
		{
			if (redir->type == RD_IN)
				str = "RD_IN";
			else if (redir->type == RD_OUT_T)
				str = "RD_OUT_T";
			else if (redir->type == RD_OUT_A)
				str = "RD_OUT_A";
			else if (redir->type == RD_HEREDOC)
				str = "RD_HEREDOC";
			else
				str = "UNKNOWN";
			printf("Redir %d: %s, type: %s\n", j, redir->content, str);
			j++;
			redir = redir->next;
		}
		if (tmp->next)
			printf("Next command block:\n");
		else
			printf("End of command block list\n");

		printf("\n");
		tmp = tmp->next;
	}
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

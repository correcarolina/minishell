/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:04:01 by cacorrea          #+#    #+#             */
/*   Updated: 2025/05/12 20:04:05 by cacorrea         ###   ########.fr       */
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

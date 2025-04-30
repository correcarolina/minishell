/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 10:18:20 by cacorrea          #+#    #+#             */
/*   Updated: 2025/04/30 10:18:23 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_one_cmd(t_cmdblock *cmdblocks)
{
	t_cmdblock	*current;

	current = cmdblocks;
	if (current->next == NULL)
		return (1);
	return (0);
}

int	is_built_in(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0 || \
		ft_strncmp(cmd, "cd", 3) == 0 || \
		ft_strncmp(cmd, "pwd", 4) == 0 || \
		ft_strncmp(cmd, "export", 7) == 0 || \
		ft_strncmp(cmd, "unset", 6) == 0 || \
		ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	return (0);
}

void	close_fd(int fd)
{
	if (fd != -1)
		close(fd);
}
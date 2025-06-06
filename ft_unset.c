/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:49:27 by cacorrea          #+#    #+#             */
/*   Updated: 2025/02/11 12:49:31 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **cmd, t_ms *mini)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (cmd[i])
	{
		if (!ft_isvalid_name(cmd[i]))
		{
			print_builtin_error(cmd[0], cmd[i], mini);
			status = 1;
		}
		else
		{
			env_rm_node(&mini->myenv, cmd[i]);
		}
		i++;
	}
	mini->exit_status = status;
	return (status);
}

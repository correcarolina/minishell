/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:39:58 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/05 20:11:13 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//gets the working directory from the env var in my t_ms struct and prints it.

int	ft_pwd(t_ms *mini)
{
	char	cwd[1024];

	if (getcwd(cwd, 1024) == NULL)
	{
		ft_putstr_fd("pwd: getcwd error\n", 2);
		mini->exit_status = 1;
		return (1);
	}
	ft_putendl_fd(cwd, 1);
	mini->exit_status = 0;
	return (0);
}

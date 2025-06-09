/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 10:39:58 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/09 19:06:36 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//gets the working directory from the env var in my t_ms struct and prints it.

int	ft_pwd(t_ms *mini)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096) == NULL)
	{
		ft_putstr_fd("pwd: getcwd error\n", 2);
		mini->exit_status = 1;
		return (1);
	}
	ft_putendl_fd(cwd, 1);
	mini->exit_status = 0;
	return (0);
}

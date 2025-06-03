/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:03:19 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/03 18:29:37 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_error1(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
}

void	ft_print_error(char *str, t_ms *mini, int err)
{
	if (err == 1)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": command not found", 2);
		mini->exit_status = 127;
	}
	else if (err == 2)
	{
		ft_print_error1(str);
		ft_putendl_fd(": numeric argument required", 2);
		mini->exit_status = 2;
	}
	else if (err == 3)
	{
		ft_print_error1(str);
		ft_putendl_fd(": No such file or directory", 2);
		mini->exit_status = 127;
	}
	else if (err == 4)
	{
		ft_print_error1(str);
		ft_putendl_fd(": Permission denied", 2);
		mini->exit_status = 126;
	}
}

void	ft_print_error2(char *str, t_ms *mini, int err)
{
	if (err == 5)
	{
		ft_print_error1(str);
		ft_putendl_fd(": Not a directory", 2);
		mini->exit_status = 126;
	}
}
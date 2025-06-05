/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:38:22 by rd-agost          #+#    #+#             */
/*   Updated: 2025/06/05 17:29:41 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_overflow(char *str)
{
	int	i;
	int	len;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	len = 0;
	while (str[i + len] && ft_isdigit(str[i + len]))
		len++;
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	if (str[0] == '-')
		return (ft_strcmp(&str[i], "9223372036854775808") > 0);
	return (ft_strcmp(&str[i], "9223372036854775807") > 0);
}

static void	ft_error_1(char **cmd, int i, t_ms *ms)
{
	if (!ft_isdigit(cmd[1][++i]) || ft_overflow(cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		ms_cleanup(ms);
		exit(2);
	}
}

int	ft_exit(char **cmd, t_ms *ms)
{
	int	exit_code;
	int	i;

	exit_code = ms->exit_status;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd[1] != NULL)
	{
		i = -1;
		++i;
		if (cmd[1][i] == '-' || cmd[1][i] == '+')
			i++;
		while (cmd[1][++i])
			ft_error_1(cmd, i, ms);
		if (cmd[2] != NULL)
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			ms->exit_status = 1;
			return (1);
		}
		exit_code = ft_atoi(cmd[1]) & 255;
	}
	ft_clear_cmdblock(&ms->cmdblocks);
	ms_cleanup(ms);
	exit(exit_code & 255);
	return (42);
}

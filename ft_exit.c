/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:38:22 by rd-agost          #+#    #+#             */
/*   Updated: 2025/06/09 18:50:03 by cacorrea         ###   ########.fr       */
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

static int	is_alpha(const char *str)
{
	if (!str || str[0] == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

static void	ft_error_1(char **cmd, t_ms *ms)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmd[1], STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	ft_clear_cmdblock(&ms->cmdblocks);
	ms_cleanup(ms);
	rl_clear_history();
	exit(2);
}

int	ft_exit(char **cmd, t_ms *ms, int p)
{
	int	exit_code;

	exit_code = ms->exit_status;
	if (p)
		ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd[1])
	{
		if (is_alpha(cmd[1]) || ft_overflow(cmd[1]))
			ft_error_1(cmd, ms);
		else if (!cmd[2])
			exit_code = ft_atoi(cmd[1]);
		else if (cmd[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			exit_code = 1;
			ms->exit_status = 1;
			return (1);
		}	
	}
	ft_clear_cmdblock(&ms->cmdblocks);
	ms_cleanup(ms);
	rl_clear_history();
	exit(exit_code & 255);
	return (42);
}

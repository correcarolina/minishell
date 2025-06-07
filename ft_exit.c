/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:38:22 by rd-agost          #+#    #+#             */
/*   Updated: 2025/06/07 16:25:17 by rd-agost         ###   ########.fr       */
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

static int	is_numeric(const char *str)
{
    int i = 0;

    if (!str || !str[0])
        return 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
    if (!str[i])
        return 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

static void	ft_error_1(char **cmd, int i, t_ms *ms)
{
	if (!is_numeric(&cmd[1][++i]) || ft_overflow(cmd[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		ft_clear_cmdblock(&ms->cmdblocks);
		ms_cleanup(ms);
		rl_clear_history();
		exit(2);
	}
}


int	ft_exit(char **cmd, t_ms *ms, int p)
{
    int	exit_code = ms->exit_status;

    if (p)
        ft_putendl_fd("exit", STDOUT_FILENO);
    if (cmd[1])
    {
		if (cmd[2])
        {
			ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
			ft_clear_cmdblock(&ms->cmdblocks);
			ms_cleanup(ms);
			rl_clear_history();
			exit(1);
        }
		ft_error_1(cmd, 0, ms);
        exit_code = ft_atoi(cmd[1]);
    }
    ft_clear_cmdblock(&ms->cmdblocks);
    ms_cleanup(ms);
    rl_clear_history();
    exit(exit_code & 255);
    return (42);
}

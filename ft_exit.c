/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:38:22 by rd-agost          #+#    #+#             */
/*   Updated: 2025/05/12 18:08:11 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_exit(char **cmd, t_ms *ms)
{
    int exit_code = ms->exit_status; // Default to last exit status
    int i;
    ft_putendl_fd("exit", STDOUT_FILENO);
    
    if (cmd[1] != NULL)
    {
        i = 0;
        if (cmd[1][i] == '-' || cmd[1][i] == '+')
            i++;
        while (cmd[1][i])
        {
            if (!ft_isdigit(cmd[1][i]))
            {
                ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
                ft_putstr_fd(cmd[1], STDERR_FILENO);
                ft_putendl_fd(": numeric argument required", STDERR_FILENO);
                ms_cleanup(ms);
                exit(2);
            }
            i++;
        }

        if (cmd[2] != NULL)
        {
            ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
            ms->exit_status = 1;
            return 1; 
        }
        exit_code = ft_atoi(cmd[1]) & 255;
    }
    ms_cleanup(ms);
    exit(exit_code & 255);
    return 42; // Never reached
}
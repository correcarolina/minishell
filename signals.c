/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:53:17 by rd-agost          #+#    #+#             */
/*   Updated: 2025/05/13 16:07:22 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


volatile sig_atomic_t g_signo = 0;

void signal_handler(int signo)
{
    g_signo = signo;
    if (g_signo == SIGINT)  // Ctrl-C
    {
        // rl_on_new_line();
        close(0);
        write(STDOUT_FILENO, "\n", 1);
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else if (signo == SIGQUIT)
    {
        write(STDOUT_FILENO, "\b\b  \b\b", 6);
        rl_redisplay();
    }
}

void setup_signals(void)
{
    signal(SIGINT, signal_handler);  // Ctrl-C
    signal(SIGQUIT, signal_handler); // Ctrl-\ .
}

void setup_child_signals(void)
{
    signal(SIGINT, SIG_DFL);   // Reset 
    signal(SIGQUIT, SIG_DFL); 
}
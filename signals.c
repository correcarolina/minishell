/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:53:17 by rd-agost          #+#    #+#             */
/*   Updated: 2025/05/25 19:32:49 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_signo = 0;  // 0 = nessun segnale

void	signal_handler(int signo)
{
	g_signo = signo;
	if (signo == SIGINT)
	{
		close(0);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signo == SIGQUIT)
	{
		write(STDOUT_FILENO, "\b\b  \b\b", 6);
		rl_redisplay();
	}
}

void	setup_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

//handles ctrl c in heredoc
void	ft_hd_ctrlc(volatile sig_atomic_t g_signo, int ex_SI, int w_fd)
{
	if (g_signo == SIGINT)
	{
		ex_SI = 1;
		g_signo = 0;
		close_fd(w_fd);
		write(1, "\n", 1);
		exit(130);
	}
}
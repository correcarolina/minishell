/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:53:17 by rd-agost          #+#    #+#             */
/*   Updated: 2025/06/06 13:27:57 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signo = 0;  // 0 = nessun segnale

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		close(0);
		g_signo = signo;
		//rl_replace_line("", 0);
		//rl_redisplay();
	}
}

void	setup_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
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
void	ft_hd_ctrlc(int signo, int ex_SI, int w_fd)
{
	if (signo == SIGINT)
	{
		ex_SI = 1;
		signo = 0;
		close_fd(w_fd);
		write(1, "\n", 1);
		close(0);
	}
}
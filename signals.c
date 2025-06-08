/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:53:17 by rd-agost          #+#    #+#             */
/*   Updated: 2025/06/08 18:28:22 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signo = 0;  // 0 = nessun segnale

void	signal_handler(int signo)
{
	//printf(GREEN "signal handler" DEFAULT);
	if (signo == SIGINT)
	{
		// printf("\n");
		// close(0);
		g_signo = 2;
		// printf(" signal %d\n", signo);
		//rl_replace_line("", 0);
		//rl_redisplay();
		// printf("\n");
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int getsingal(t_ms *mini)
{
	if (g_signo == SIGINT)
	{
		g_signo = 0;
		// printf("130 SI VOLA\n");
		return (130);
	}
	// printf("ESCO DIO MERDA\n");
	return (mini->exit_status);
}

/* void	setup_signals(t_ms *mini)
{

	if (g_signo == SIGINT)
		mini->exit_status = 130;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
} */

void	child_sighand(int sig)
{
	if (sig == SIGINT)
	{
		g_signo = SIGINT;
		rl_replace_line("", 0);
		rl_redisplay();
		if (isatty(STDOUT_FILENO))
			printf("\n");
	}
	else if (sig == SIGQUIT)
	{
		g_signo = SIGQUIT;
		rl_replace_line("", 0);
		rl_redisplay();
		if (isatty(STDOUT_FILENO))
			printf("Quit (core dumped)\n");
	}
}

void	setup_child_signals(void)
{
	signal(SIGINT, child_sighand);
	signal(SIGQUIT, child_sighand);
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, ft_hd_ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

//handles ctrl c in heredoc
void	ft_hd_ctrlc(int signo)
{
	if (signo == SIGINT)
	{
		//g_signo = 0;
		//close_fd(w_fd);
		rl_replace_line("", 0);
		write(1, "\n", 1);
		g_signo = SIGINT;
		close(0);
		//exit(130);
	}
}
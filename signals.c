/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:53:17 by rd-agost          #+#    #+#             */
/*   Updated: 2025/06/09 15:24:57 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signo = 0;

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_signo = 2;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	getsingal(t_ms *mini)
{
	if (g_signo == SIGINT)
	{
		g_signo = 0;
		return (130);
	}
	return (mini->exit_status);
}

void	child_sighand(int sig)
{
	if (sig == SIGINT)
	{
		g_signo = SIGINT;
		if (isatty(STDOUT_FILENO))
			printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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

void	ft_hd_ctrlc(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		g_signo = SIGINT;
		close(0);
	}
}

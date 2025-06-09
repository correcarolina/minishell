/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:31:04 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/09 13:11:09 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_cmds(t_ms *mini, char *line)
{
	if (handle_heredocs(mini->cmdblocks, mini) == -1)
	{
		ft_clear_cmdblock(&mini->cmdblocks);
		free(line);
		line = NULL;
		dup2(mini->stdinout_copy[0], STDIN_FILENO);
		dup2(mini->stdinout_copy[1], STDOUT_FILENO);
		return (1);
	}
	execute_cmdblocks(mini->cmdblocks, mini);
	ft_clear_cmdblock(&mini->cmdblocks);
	return (0);
}

static int	parse_n_create_cmdblocks(t_ms *mini, char *line, t_list **input)
{
	tokenize(mini, line, input);
	if (ft_parse(*input) == -1)
	{
		free(line);
		line = NULL;
		ft_clear_lst(input);
		dup2(mini->stdinout_copy[0], STDIN_FILENO);
		dup2(mini->stdinout_copy[1], STDOUT_FILENO);
		return (1);
	}
	mini->cmdblocks = ft_create_cmdblock(*input);
	ft_clear_lst(input);
	return (0);
}

static int	handle_line(t_ms *mini, char *line)
{
	t_list		*input;

	input = NULL;
	if (ft_isvalid_input((const char *)line))
	{
		if (parse_n_create_cmdblocks(mini, line, &input) != 0)
			return (1);
		if (process_cmds(mini, line) != 0)
			return (1);
		free(line);
		line = NULL;
		dup2(mini->stdinout_copy[0], STDIN_FILENO);
		dup2(mini->stdinout_copy[1], STDOUT_FILENO);
		return (0);
	}
	return (0);
}

void	run_shell_loop(t_ms *mini)
{
	char	*line;

	signal(SIGINT, signal_handler);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		line = readline(GREEN "minishell> " DEFAULT);
		mini->exit_status = getsingal(mini);
		if (line == NULL && g_signo != SIGINT)
		{
			dup2(mini->stdinout_copy[0], 0);
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		if (g_signo == SIGINT)
		{
			dup2(mini->stdinout_copy[0], 0);
		}
		add_history(line);
		handle_line(mini, line);
	}
}

int	main(int ac, char **av, char **env)
{
	t_ms	*mini;

	(void) **av;
	if (ac != 1)
		return (0);
	mini = ft_init(env);
	if (!mini)
		return (1);
	run_shell_loop(mini);
	ms_cleanup(mini);
	rl_clear_history();
	return (g_signo);
}

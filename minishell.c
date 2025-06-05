/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:31:04 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/05 20:31:23 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_cmds(t_ms *mini, char *line)
{
	if (handle_heredocs(mini->cmdblocks, mini) == -1)
	{
		ft_putendl_fd("minishell: heredoc error", STDERR_FILENO);
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

	while (1)
	{
		g_signo = 0;
		line = readline(GREEN "minishell> " DEFAULT);
		if (g_signo == SIGINT)
		{
			dup2(mini->stdinout_copy[0], 0);
			continue ;
		}
		if (line == NULL && g_signo != SIGINT)
		{
			dup2(mini->stdinout_copy[0], 0);
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
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
	setup_signals();
	run_shell_loop(mini);
	ms_cleanup(mini);
	rl_clear_history();
	return (g_signo);
}

/* ************************************************************************** */
/*jun 5
 static int	handle_line(t_ms *mini, char *line)
{
	t_list		*input;

	input = NULL;
	if (ft_isvalid_input((const char *)line))
	{
		tokenize(mini, line, &input);
		if (ft_parse(input) == -1)
		{
			free (line);
			line = NULL;
			ft_clear_lst(&input);
			dup2(mini->stdinout_copy[0], STDIN_FILENO);
			dup2(mini->stdinout_copy[1], STDOUT_FILENO);
			return (1);
		}
		mini->cmdblocks = ft_create_cmdblock(input);//si puo mettere dentro ft-parse?
		ft_clear_lst(&input);
		if (process_cmds(mini, line) != 0)
			return (1);
		free (line);
		line = NULL;
		dup2(mini->stdinout_copy[0], STDIN_FILENO);
		dup2(mini->stdinout_copy[1], STDOUT_FILENO);
		return (0);
	}
	return (0);
} */
/*  MAIN JUN 5
int	main(int ac, char **av, char **env)
{
	char		*line;
	t_ms		*mini;

	(void) **av;
	if (ac != 1)
		return (0);
	mini = ft_init(env);
	if (!mini)
		return (1);
	setup_signals();
	while (1)
	{
		g_signo = 0;
		line = readline(GREEN "minishell> " DEFAULT);
		if (g_signo == SIGINT)
		{
			dup2(mini->stdinout_copy[0], 0);
			continue ;
		}
		if (line == NULL && g_signo != SIGINT)
		{
			dup2(mini->stdinout_copy[0], 0);
			write(STDOUT_FILENO, "exit\n", 5);
			break ;
		}
		add_history(line);
		handle_line(mini, line);
	}
	ms_cleanup(mini);
	if (line == NULL && g_signo != SIGINT)
		exit(0);
	rl_clear_history();
	return (mini->exit_status);
}
 */
/*original main that worked well until 2/06/25
 int main(int ac, char **av, char **env)
{
	char		*line;
	t_list		*input;
	t_ms		*mini;

	(void) **av;
	if (ac != 1)
		return (0);
	input = NULL;
	mini = ft_init(env);
	if (!mini)
		return (1);
	setup_signals();
	while(1)
	{
		g_signo = 0;
        line = readline(GREEN "minishell> " DEFAULT);
		if (g_signo == SIGINT)
		{
			dup2(mini->stdinout_copy[0], 0);
			continue ;
		}
        if (line == NULL && g_signo != SIGINT)
        {
			dup2(mini->stdinout_copy[0], 0);
            write(STDOUT_FILENO, "exit\n", 5);
            break;
        }
        add_history(line);
		if (ft_isvalid_input((const char *)line))
		{
			tokenize(mini, line, &input);
			if (ft_parse(input) == -1)
			{
				free (line);
				line = NULL;
				ft_clear_lst(&input);
				dup2(mini->stdinout_copy[0], STDIN_FILENO);
				dup2(mini->stdinout_copy[1], STDOUT_FILENO);
				continue ;
			}
			mini->cmdblocks = ft_create_cmdblock(input);//si puo mettere dentro ft-parse?
			ft_clear_lst(&input);
			if (handle_heredocs(mini->cmdblocks, mini) == -1)
			{
				ft_putendl_fd("minishell: heredoc error", STDERR_FILENO);
				ft_clear_cmdblock(&mini->cmdblocks);
				free(line);
				line = NULL;
				dup2(mini->stdinout_copy[0], STDIN_FILENO);
				dup2(mini->stdinout_copy[1], STDOUT_FILENO);
				continue ;
			}
			execute_cmdblocks(mini->cmdblocks, mini);
			ft_clear_cmdblock(&mini->cmdblocks);
		}
		free (line);
		line = NULL;
		dup2(mini->stdinout_copy[0], STDIN_FILENO);
		dup2(mini->stdinout_copy[1], STDOUT_FILENO);
	}
	ms_cleanup(mini);
	return (mini->exit_status);
} */

/* //questo main senza readline non ha leaks 7/4/25
int	main (int ac, char **av, char **env)
{
	char		*line;
	t_list		*input;
	t_ms		*mini;

	if (ac != 2)
		return (printf("only one arg required\n"), 0);
	mini = (t_ms *)malloc(sizeof(t_ms));
	if (!mini)
		return (1);//da qui in poi si puo fare ft_init
	input = NULL;
	mini->myenv = ft_env_cpy(mini->myenv, env);
	mini->cwd = ft_getenv_var(mini, "PWD");
	mini->exit_status = 0;
	line = av[1];
	if (ft_isvalid_input((const char *)line))
	{
		tokenize(mini, line, &input);
		if (!input)// solo per DB, questo msg va levato. deve restituire il prompt
			ft_putstr_fd("Error: input is NULL after tokenize\n", 2);
		ft_parse(input);
		debug_printer(input);
		ft_clear_lst(&input);
	}
	ms_cleanup(mini);
	free(mini);
	return (0);
} */

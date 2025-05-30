/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:31:04 by cacorrea          #+#    #+#             */
/*   Updated: 2025/05/29 13:45:04 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" //init_data  envp_init

#define RED "\001\033[1;31m\002"
#define YELLOW "\001\033[1;33m\002"
#define GREEN "\001\033[1;92m\002"
#define BLUE "\001\033[1;34m\002"
#define CYAN "\001\033[1;36m\002"
#define PURPLE "\001\033[1;35m\002"
#define WHITE "\001\033[1;37m\002"
#define AQUA "\001\033[1;36m\002"
#define DEFAULT "\001\033[0m\002"

void	ms_cleanup(t_ms *ms)
{
	if (ms->cwd)
		free(ms->cwd);
	if (ms->myenv)
		env_clear_lst(&ms->myenv);
	dup2(ms->stdinout_copy[0], STDIN_FILENO);
	dup2(ms->stdinout_copy[1], STDOUT_FILENO);
	close_fd(ms->stdinout_copy[0]);//da vedere se c'e bisogno di chiudere
	close_fd(ms->stdinout_copy[1]);
	ms->stdinout_copy[0] = -1;
	ms->stdinout_copy[1] = -1;
}

int main(int ac, char **av, char **env)
{
	char		*line;
	t_list		*input;
	t_ms		*mini;

	(void) **av;
	if (ac != 1)
		return (0);
	mini = (t_ms *)malloc(sizeof(t_ms));
	if (!mini)
		return (1);//da qui in poi si puo fare ft_init
	*mini = (t_ms){0};
	input = NULL;
	mini->cmdblocks = NULL;
	mini->myenv = ft_env_cpy(NULL, env);
	mini->cwd = ft_getenv_var(mini, "PWD");
	mini->stdinout_copy[0] = dup(STDIN_FILENO);//serve per heredoc e per ripristinare 
	mini->stdinout_copy[1] = dup(STDOUT_FILENO);//stdin-out alla fine se sei nel parent
	/***************chiudere queste copie a fine programma dopo il loro ripristino*/
	if (mini->stdinout_copy[0] == -1 || mini->stdinout_copy[1] == -1)
	{
		perror("dup");
		ms_cleanup(mini);
		return (1);
	}
	mini->exit_status = 0;
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
	free(mini);
	return (mini->exit_status);
}


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


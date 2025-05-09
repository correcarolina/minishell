/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:31:04 by cacorrea          #+#    #+#             */
/*   Updated: 2025/04/26 19:00:03 by rd-agost         ###   ########.fr       */
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
	close(ms->stdinout_copy[0]);//da vedere se c'e bisogno di chiudere
	close(ms->stdinout_copy[1]);
}

int	main (int ac, char **av, char **env)
{
	char		*line;
	t_list		*input;
	t_cmdblock	*head;
	t_ms		*mini;

	(void) **av;
	if (ac != 1)
		return (0);
	mini = (t_ms *)malloc(sizeof(t_ms));
	if (!mini)
		return (1);//da qui in poi si puo fare ft_init
	input = NULL;
	mini->myenv = ft_env_cpy(mini->myenv, env);
	mini->cwd = ft_getenv_var(mini, "PWD");
	mini->stdinout_copy[0] = dup(STDIN_FILENO);//serve per heredoc e per ripristinare 
	mini->stdinout_copy[1] = dup(STDOUT_FILENO);//stdin-out alla fine se sei nel parent
	/***************chiudere queste copie a fine programma dopo il loro ripristino*/
	if (mini->stdinout_copy[0] == -1 || mini->stdinout_copy[1] == -1)
	{
		perror("dup");
		free(mini);
		return (1);
	}
	mini->exit_status = 0;
	//BD	printf("il valore di cwd e: %s\n", mini->cwd);
	while(1)
	{
		//signals setting
		line = readline(GREEN "minishell> " DEFAULT);
	//DB	printf("%s\n", line);
		add_history(line);
		if(ft_strcmp("exit", line) == 0)
		{
			rl_clear_history();
			//free_all(&mini->myenv->key);
			printf("exit\n");
			break;/*oppure exit(0);*/
		}
		else if (ft_isvalid_input((const char *)line))
		{
			tokenize(mini, line, &input);
			ft_parse(input);
			head = ft_create_cmdblock(input);//si puo mettere dentro ft-parse?
			ft_clear_lst(&input);
			execute_cmdblocks(head, mini);
		//	execute_command(head, &mini->myenv, mini );
			
		}
		/* if (ft_strncmp(line, "pwd", 3) == 0)
			ft_pwd(mini);
		if (ft_strncmp(line, "env", 3) == 0)
			ft_env(mini);
		if (ft_strncmp(line, "export", 6) == 0)
			ft_export(mini); */
		//else (error, quotes not closed and return prompt);
		free (line);
	}
	ms_cleanup(mini);
	free(mini);
	return (0);
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


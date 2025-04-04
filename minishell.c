/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 12:31:04 by cacorrea          #+#    #+#             */
/*   Updated: 2025/01/30 12:31:07 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" //init_data  envp_init

# define RED "\001\033[1;31m\002"
# define YELLOW "\001\033[1;33m\002"
# define GREEN "\001\033[1;92m\002"
# define BLUE "\001\033[1;34m\002"
# define CYAN "\001\033[1;36m\002"
# define PURPLE "\001\033[1;35m\002"
# define WHITE "\001\033[1;37m\002"
# define AQUA "\001\033[1;36m\002"
# define DEFAULT "\001\033[0m\002"



int	main (int ac, char **av, char **env)
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
	input = NULL;
	mini->myenv = ft_env_cpy(mini->myenv, env);
	mini->cwd = ft_getenv_var(mini, "PWD");
	mini->exit_status = 0;
	while(1)
	{
		//signals setting
		line = readline(GREEN "minishell> " DEFAULT);
	//DB	printf("%s\n", line);
		//add history se line non e vuota
		if (ft_isvalid_input((const char *)line))
		{
			
			tokenize(mini, line, &input);
			if (!input)/* solo per DB, questo msg va levato. deve restituire il prompt */
			    ft_putstr_fd("Error: input is NULL after tokenize\n", 2);
			ft_parse(input);
			debug_printer(input);
			ft_clear_lst(&input);
		}//queste le devo gestire dopo, una fn che le gestisce tutte quando ho gia i cmd 
		//in un array cmd args
		
		/* if (ft_strncmp(line, "pwd", 3) == 0)
			ft_pwd(mini);
		if (ft_strncmp(line, "env", 3) == 0)
			ft_env(mini);
		if (ft_strncmp(line, "export", 6) == 0)
			ft_export(mini); */
		//else (error, quotes not closed and return prompt);
		free (line);
	}
	env_clear_lst(&mini->myenv);
	free(mini);
	return (0);
}


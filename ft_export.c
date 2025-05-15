/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:25:55 by cacorrea          #+#    #+#             */
/*   Updated: 2025/02/11 12:25:57 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_print(t_envlst *env)
{
	t_envlst	*temp;

	temp = env;
	while (temp)
	{
		if (temp->value)
			printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
		else
			printf("declare -x %s\n", temp->key);
		temp = temp->next;
	}
}

//es: se non e un arg valido: minishell: export: '?????': not a valid identifier
void	print_export_error(char *builtin, char *arg, t_ms *mini)
{
	mini->exit_status = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(builtin, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	export_loop(char *str, t_ms	*mini)
{
	int			i;
	char		*key;

	i = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	if (!key)
	{
		perror("malloc");
		return (1);
	}
	if (!ft_isvalid_name(key))
	{
		print_export_error("export", str, mini);
		return (1);
	}
	env_rm_node(&mini->myenv, key);
	env_append_node(&mini->myenv, env_new_node(str));
	free(key);
	return (0);
}

int	ft_export(char **cmd, t_ms *mini)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (cmd[1] == NULL)//se non ci sono argomenti
		env_print(mini->myenv);
	else//else fare un ciclo per tutti gli args
	{
		while (cmd[i] != NULL)
		{
			if (export_loop(cmd[i], mini) == 1)
				status = 1;
			i++;
		}
	}
	mini->exit_status = status;
	return (status);
}
	
	//else
		//msg errore (export: 'str': not a valid identifier)ma continua nel ciclo
	//cacorrea@c1r5p3:~/sgoinfre/minishell$ export =
	//bash: export: `=': not a valid identifier
	//cacorrea@c1r5p3:~/sgoinfre/minishell$ export=
	//cacorrea@c1r5p3:~/sgoinfre/minishell$ 
	//cosa li passo?: 	una str: env ciao carolina
	//					una matrice:	env'\0'
	//									ciao'\0'
	//									carolina'\0'
	//					o una lista: 	env'\0' -->  ciao'\0' -->  carolina'\0'
	
	//se ci sono gli args == sto settando una var:
	//se ce la chiave eliminarla, se non ce non fa niente, lo fa automaticamente env_rm_node
	//e poi appendere il nodo
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

static void	print_export_error(char *str, t_ms *mini)
{
	mini->exit_status = 1;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static void	export_loop(char *str, t_ms	*mini)
{
	int			i;
	char		*key;

	i = 0;
	if (!ft_strchr(str, '=') || ft_strchr(str, '=') == str)
	{
		print_export_error(str, mini);
		return ;
	}
	while (str[i] != '\0' && str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	printf("👽key: %s\n", key);/************db**************/
	if (ft_isvalid_name(key))
	{
		env_rm_node(&mini->myenv, key);
		env_append_node(&mini->myenv, env_new_node(str));
	}
	else
		print_export_error(str, mini);
	free(key);
}

void	ft_export(char **cmd, t_ms *mini)
{
	int	j;

	j = 1;
	if (cmd[1] == NULL)//se non ci sono argomenti
	{
		env_print(mini->myenv);
		return ;//devo salvare lo stato di uscita?
	}
	else//else fare un ciclo per tutti gli args
	{
		while (cmd[j] != NULL)
		{
			export_loop(cmd[j], mini);
			j++;
		}
	}
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
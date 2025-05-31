/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:25:55 by cacorrea          #+#    #+#             */
/*   Updated: 2025/05/31 23:27:08 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//takes the "+" out of the string and recomposes the string
//s1: ciao      append: aaa+=mondo		return: aaa=ciaomondo
static char	*ft_getstr_export(char *s1, char *append)
{
	char	*str;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(append), sizeof(char));
	if (!str)
		return (perror("malloc"), NULL);
	while (append[j] && append[j] != '+')
		str[i++] = append[j++];
	j++;
	str[i++] = append[j++];
	if (s1 != NULL)
	{
		while (s1[k])
			str[i++] = s1[k++];
	}
	while (append[j])
		str[i++] = append[j++];
	return (str);
}

static int	export_append(char *str, char *old_key, t_ms *mini)
{
	char	*trimmed_key;
	char	*value;
	char	*new_value;

	value = NULL;
	trimmed_key = ft_substr(str, 0, ft_strlen(str) - 1);
	if (!trimmed_key)
		return (perror("malloc"), 1);
	if (!ft_isvalid_name(trimmed_key))
	{
		print_builtin_error("export", old_key, mini);
		free(trimmed_key);
		return (1);
	}
	value = ft_getenv_var(mini, trimmed_key);
	new_value = ft_getstr_export(value, old_key);
	if (value)
		free(value);
	if (!new_value)
		return (free(trimmed_key), 1);
	env_rm_node(&mini->myenv, trimmed_key);
	env_append_node(&mini->myenv, env_new_node(new_value));
	free(trimmed_key);
	free(new_value);
	return (0);
}

static int	export_set(char *key, char *str, t_ms *mini)
{
	if (!ft_isvalid_name(key))
	{
		print_builtin_error("export", str, mini);
		return (1);
	}
	if (ft_strchr(str, '=') == NULL)
	{
		if (env_get_node(&mini->myenv, key) == NULL)
			env_append_node(&mini->myenv, env_new_node(key));
		return (0);
	}
	env_rm_node(&mini->myenv, key);
	env_append_node(&mini->myenv, env_new_node(str));
	return (0);
}

static int	export_loop(char *str, t_ms	*mini)
{
	int			i;
	int			status;
	char		*key;

	i = 0;
	status = 0;
	while (str[i] != '\0' && str[i] != '=')
		i++;
	key = ft_substr(str, 0, i);
	if (!key)
		return (perror("malloc"), 1);
	if (i >= 2 && key[i - 1] == '+')
	{
		status = export_append(key, str, mini);
		free(key);
		return (status);
	}
	status = export_set(key, str, mini);
	free(key);
	return (status);
}

int	ft_export(char **cmd, t_ms *mini)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (cmd[1] == NULL)//se non ci sono argomenti
		env_export_print(mini->myenv);
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
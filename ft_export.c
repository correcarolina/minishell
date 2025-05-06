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

//Constructs a string of the form "key=value"
static char	*ft_expandedstr(char *key, char *value)
{
	char	*str;
	char	*temp;

	if (!value && !key)
		return (NULL);
	temp = ft_strjoin(key, "=");
	str = ft_strjoin(temp, value);
	free (temp);
	return (str);
}

//Recursively expands all '$' occurrences in the input string
static char	*ft_export_expansion(t_ms mini, char *s)
{
	char	*s1;
	char	*expanded;
	char	*s3;
	char	*result;
	int		i;
	char	*ptr;

	i = 0;
	expanded = NULL;
	while(s[i] && s[i] != '$')
		i++;
	s1 = ft_substr(s, 0, i);
	if (s[i] == '$')
	{
		i++;
		ptr = &s[i];
		expanded = ft_dollar_expansion(mini, &ptr);
	}
	s3 = ft_strdup(&s[i]);
	result = ft_strjoin_free(s1, expanded);
	if (ft_strchr(s3, '$'))
		expanded = ft_export_expansion(mini, s3);
	else
		expanded = ft_strdup(s3);
	result = ft_strjoin_free(result, expanded);
	free(expanded);
	free(s3);
	return (s1);
}

/*da sistemare e testare*********************/

void	ft_export(char **cmd, t_ms *mini)
{
	t_envlst	*temp;
	int			i;
	int 		j;
	char		*str;
	char		*key;

	temp = mini->myenv;
	i = 0;
	j = 1;
	str = cmd[1];
	if (cmd[1] == NULL)//se non ci sono argomenti
	{
		while (temp)
		{
			printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
			temp = temp->next;
		}
	}
	else//else fare un ciclo per tutti gli args
	{
		while (cmd[j] != NULL)
		{
			str = cmd[j];
			if (!ft_strchr(str, '=') || ft_strchr(str, '=') == str)
			{
				ft_putstr_fd("minishell: 👹export: `", 2);
				ft_putstr_fd(str, 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				mini->exit_status = 1;
				j++;
				continue;
			}
			i = 0;
			while (str[i] != '\0' && str[i] != '=')
				i++;
			key = ft_substr(str, 0, i);
			printf("👽key: %s\n", key);
			printf("%d\n", ft_isvalid_name(key));
			if (ft_isvalid_name(key))
			{//qui non sta funzionando
				env_rm_node(&mini->myenv, key);
				env_append_node(&mini->myenv, env_new_node(str));	
			}
			else
			{
				ft_putstr_fd("minishell: 😾export: `", 2);
				ft_putstr_fd(str, 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				mini->exit_status = 1;
			}
			free(key);
			j++;
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
	//env_rm_node(&temp, ft_substr(arg[1], quello che ce prima del =));
	//env_append_node(&temp, env_new_node(arg[1]));
}

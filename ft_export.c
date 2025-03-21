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

void	ft_export(t_ms	*mini)//anche il cmd come matrice
{
	t_envlst	*temp;
	int			i;
	char		*str1;//da levare arriva con gli argomenti della funzione
	char		*str;
	char		*key;
	char		*expanded;

	temp = mini->myenv;
	i = 0;
	str = NULL;
	str1 = "wwwwwwww=carolina";//solo per sostituire il primo argomento str = arg[1]
	//if se ce solo export senza argomenti: stampa e poi return;
	while (temp)
	{
		printf("declare -x %s=\"%s\"\n", temp->key, temp->value);
		temp = temp->next;
	}
	//else fare un ciclo per tutti gli args
	if (!ft_strchr(str, '='))//cerca se ce un =, se non lo trova esce
		return ;//giusto cosi, bash non da errore, ritorna il prompt
	while (str1[i] != '\0' && str1[i] != '=')
		i++;
	key = ft_substr(str1, 0, i);
	if (ft_isvalid_name(key))
	{
		env_rm_node(&mini->myenv, key);
		if (ft_strchr(&str1[i], '$'))//expand the var
		{
			expanded = ft_export_expansion(*mini, &str1[i]);

			str = ft_expandedstr(key, expanded);
		}
		env_append_node(&mini->myenv, env_new_node(str));	
	}
	//else
		//msg errore (export: 'str': not a valid identifier)ma continua nel ciclo
	free(key);
	return;
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

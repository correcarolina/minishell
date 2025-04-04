/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singlequote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:28:37 by cacorrea          #+#    #+#             */
/*   Updated: 2025/02/13 17:28:40 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//questa funziona, main in borradores con str = 'ciao stringa'*************
//returns the len of a single quoted string without the quotes
static int	sq_strlen(char *str)
{
	int	i;

	i = 1;
	if (!str || str[0] != S_QUOTE)
		return (0);
	while (str[i] && str[i] != S_QUOTE)
		i++;
	if (str[i] == '\0')
		return (0);
	return (i - 1);
}

//returns a copy of the string inside the single quotes
char	*singlequote(char **str)
{
	int		i;
	int		len;
	char	*word;

	i = 0;
	len = sq_strlen(*str);
	word = (char *)ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	while (i < len)
	{
		if (**str == S_QUOTE)
			(*str)++;
		else
			word[i++] = *(*str)++;
	}
	while (**str && **str != S_QUOTE)
		word = ft_get_plain_word(str, word);
	if (**str == S_QUOTE)
		(*str)++;
	return (word);
}

/*expands the env variables and the $? and returns a copy of value
@str: the string after the $*/
char	*ft_dollar_expansion(t_ms mini, char **str)
{
	size_t		i;
	char		*name;
	char		*value = NULL;

	i = 0;
	if (**str == '\0' || ft_isspace(**str) || **str == D_QUOTE)
		return (ft_chartostr('$'));
	else if (**str == '?')
	{
		(*str)++;
		printf("sono un segnale/n");//TEMPORANEO
		return (NULL);/*(ft_itoa(g_signal));*/
	}
	else if (**str != '_' && !ft_isalpha(**str))
	{
		(*str)++;//cosa fa se trova $.1var cioe un name non valido?
		return (ft_strdup(""));//salta il primo char dopo $ e poi passa al seguente token
	}
	while ((*str)[i] != '\0' && (ft_isalnum((*str)[i]) || (*str)[i] == '_'))
		i++;
	name = ft_substr(*str, 0, i);//checks for NULL in getenv_var
	value = ft_getenv_var(&mini, name);
	free(name);
	(*str) += i;
	return (value);
}

//returns a copy of the string inside the double quotes
char	*doublequote(t_ms mini, char **str)
{
	char	*word;

	word = ft_calloc(1, sizeof(char));
	if (!word)
		return (NULL);
	(*str)++;//skips the first double quote
	while (**str && **str != D_QUOTE)
	{
		if (**str == '$')
		{
			(*str)++;
			word = ft_get_expansion(mini, str, word);
		}
		else
			word = ft_get_plain_word(str, word);
	}
	if (**str == D_QUOTE)
		(*str)++;
	return (word);
}


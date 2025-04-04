/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:56:34 by cacorrea          #+#    #+#             */
/*   Updated: 2025/02/18 09:56:36 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if the current char found is not a dollar sign $, appends this char to word

char	*ft_get_plain_word(char **str, char *word)
{
	char	*temp;
	char	*current_char;

	current_char = ft_chartostr(**str);
	temp = ft_strjoin(word, current_char);
	free (word);
	free (current_char);
	word = temp;
	(*str)++;
	return (word);
}

//if the current char of str is $, handles the expansion

char	*ft_get_expansion(t_ms mini, char **str, char *word)
{
	char	*temp;
	char	*expanded;

	expanded = ft_dollar_expansion(mini, str);
	if (!expanded)
		return (word);
	temp = ft_strjoin(word, expanded);
	free (word);
	word = temp;
	free(expanded);
	return (word);
}

//gets a token from the input string checking one char at a time 

char	*ft_get_token(t_ms mini, char **str)
{
	char	*token;

	token = (char *)ft_calloc(1, sizeof(char));
	if (! token)
		return (NULL);
	while (**str && !ft_isspace(**str) && !ft_ismetachar(**str))
	{
		if (**str == '$')
		{
			(*str)++;
			token = ft_get_expansion(mini, str, token);
		}
		else if (**str == D_QUOTE)
			token = ft_strjoin_free(token, doublequote(mini, str));
		else if (**str == S_QUOTE)
			token = ft_strjoin_free(token, singlequote(str));
		else
			token = ft_get_plain_word(str, token);
	}
	return (token);
}

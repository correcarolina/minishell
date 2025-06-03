/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 09:56:34 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/03 12:20:02 by cacorrea         ###   ########.fr       */
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

static char	*ft_expand_variable(t_ms mini, char **str, char *token)
{
	(*str)++;
	return (ft_get_expansion(mini, str, token));
}

//gets a token from the input string checking one char at a time 
char	*ft_get_token(t_ms mini, char **str, int hd)
{
	char	*token;

	token = (char *)ft_calloc(1, sizeof(char));
	if (! token)
		return (NULL);
	while (**str && ft_isspace(**str))
		(*str)++;
	if ((**str == D_QUOTE || **str == S_QUOTE) && hd == 1)
		hd = 42;
	while (**str && !ft_isspace(**str) && !ft_ismetachar(**str))
	{
		if (**str == '$' && hd != 1)
			token = ft_expand_variable(mini, str, token);
		else if (**str == D_QUOTE)
			token = ft_strjoin_free_both(token, doublequote(mini, str));
		else if (**str == S_QUOTE)
			token = ft_strjoin_free_both(token, singlequote(str));
		else
			token = ft_get_plain_word(str, token);
	}
	if (hd == 42)
		token = ft_strjoin("'", token);
	return (token);
}

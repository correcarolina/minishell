/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:50:59 by cacorrea          #+#    #+#             */
/*   Updated: 2025/01/31 17:51:03 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_operator(char **str)
{
	char	*operator;

	operator = NULL;
	if (**str == '|')
		operator = ft_chartostr('|');
	else if (**str == '>' && *(*str + 1) == '>')
	{
		operator = ft_strdup(">>");
		(*str)++;
	}
	else if (**str == '>')
		operator = ft_chartostr('>');
	else if (**str == '<' && *(*str + 1) == '<')
	{
		operator = ft_strdup("<<");
		(*str)++;
	}
	else if (**str == '<')
		operator = ft_chartostr('<');
	(*str)++;
	return (operator);
}

static char	*handle_token(t_ms mini, char **str)
{
	char	*word;

	word = NULL;
	if (ft_ismetachar(**str))
		word = ft_operator(str);
	else
		word = ft_get_token(mini, str);
	return (word);
}

//splits the input, and put the tokens into a linked list
void	tokenize(t_ms *mini, char *str, t_list **input)
{
	char	*word;

	if (str == NULL || ft_isempty_str(str))
		return ;
	while (*str)
	{
		while (*str && isspace(*str))
			str++;
		if (*str == '\0')
			break ;
		word = handle_token(*mini, &str);
		if (word != NULL && *word != '\0')
			ft_append_node(input, ft_lstnew(word));
//non posso liberare word perche deve rimanere dentro il nodo
	}
}

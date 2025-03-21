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

/*cheks number of quotes, even nb returns 1, odd nb returns 0*/

int	paired_quotes(const char *str)
{
	int	i;
	int	single_q;
	int	double_q;

	i = 0;
	single_q = 0;
	double_q = 0;
	while (str[i] != '\0')
	{
		if (str[i] == D_QUOTE && (single_q % 2 == 0))
			double_q++;
		else if (str[i] == S_QUOTE && (double_q % 2 == 0))
			single_q++;
		i++;
	}
	if ((double_q % 2 == 0) && (single_q % 2 == 0))
		return (1);
	else
		ft_putstr_fd("error: open quotes\n", 2);
	return (0);
}

char	*ft_operator(char **str)
{
	char 	*operator;

	operator = NULL;
	if (**str == '|')
		operator = ft_chartostr('|');
	else if (**str == '>' && *(*str + 1) == '>')
	{
		operator = ft_strdup(">>");
		(*str)++;
	}
	else if (**str =='>')
		operator = ft_chartostr('>');
	else if (**str == '<' && *(*str + 1) == '<')
	{
		operator = ft_strdup("<<");
		(*str)++;
	}
	else if (**str =='<')
		operator = ft_chartostr('<');
	(*str)++;
	return (operator);
}

char	*handle_token(t_ms mini, char **str)
{
	char 	*word;

	word = NULL;
	if (**str == S_QUOTE)
		word = singlequote(str);	
	else if (**str == D_QUOTE)
		word = doublequote(mini, str);
	else if (ft_ismetachar(**str))
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
			break;
		word = handle_token(*mini, &str);
		if (word != NULL && *word != '\0')
			ft_append_node(input, ft_lstnew(word));
//non posso liberare word perche deve rimanere dentro il nodo
	}
}

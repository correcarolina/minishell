/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:50:59 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/03 13:56:56 by cacorrea         ###   ########.fr       */
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

/* static char	*handle_token(t_ms mini, char **str)
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
} */

static void	handle_operator(char **str, t_list **input)
{
	char	*word;

	word = ft_operator(str);
	if (word != NULL)
		ft_append_node(input, ft_lstnew(word));
}

static int	last_is_heredoc(t_list *lst)
{
	t_list	*last;

	last = ft_lstlast(lst);
	if (last == NULL || last->content == NULL)
		return (0);
	if (ft_strncmp(last->content, "<<", 3) == 0)
		return (1);
	return (0);
}

static void	handle_word(t_ms *mini, char **str, t_list **input)
{
	char	*word;
	t_list	*temp;
	int		hd;

	hd = 0;
	if (last_is_heredoc(*input))
		hd = 1;
	word = ft_get_token(*mini, str, hd);
	if (word != NULL)/*  && *word != '\0' levato per segfault in caso di ""*/
	{
		if (is_str_operator(word))
		{
			temp = ft_lstnew(word);
			temp->type = ARG;
			ft_append_node(input, temp);
		}
		else
			ft_append_node(input, ft_lstnew(word));
	}
}

//takes the input string and split it in tokens added at a parsing t_list
void	tokenize(t_ms *mini, char *str, t_list **input)
{
	while (*str)
	{
		while (*str && isspace(*str))
			str++;
		if (*str == '\0')
			break ;
		if (ft_ismetachar(*str))
			handle_operator(&str, input);
		else
			handle_word(mini, &str, input);
	}
}

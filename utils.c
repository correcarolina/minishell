/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:07:28 by cacorrea          #+#    #+#             */
/*   Updated: 2025/02/05 11:07:31 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns 1 if the sring is NULL or if it is made up of only spaces
//returns 0 if a non space char is found
int	ft_isempty_str(const char *str)
{
	if (!str || str[0] == '\0')
		return (1);
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

/*checks only for the metacharacters that we need in this project,
if is pipe or redirect returns 1, else returns 0*/
int	ft_ismetachar(int c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

/*checks if the string contains only one operator | , >>, <<, >, <
Helps the parser distinguish between actual operators and quoted strings
containing characters like '|', '>', or '<'*/
int	is_str_operator(char *str)
{
	if ((ft_strncmp(str, "|", 2) == 0) || \
		(ft_strncmp(str, ">>", 3) == 0) || \
		(ft_strncmp(str, "<<", 3) == 0) || \
		(ft_strncmp(str, ">", 2) == 0) || \
		(ft_strncmp(str, "<", 2) == 0))
		return (1);
	return (0);
}

//checks if a string is a valid variable name
int	ft_isvalid_name(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (0);
	while(str[i] != '\0' && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

//concatenates two strings while freeing the first one
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}


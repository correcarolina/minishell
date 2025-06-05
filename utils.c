/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:07:28 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/05 19:53:16 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	i = 0;
	if (!str)
		return (0);
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (0);
	while (str[i] != '\0')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 11:07:28 by cacorrea          #+#    #+#             */
/*   Updated: 2025/05/30 17:39:59 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//es: se non e un arg valido: minishell: export: '?????': not a valid identifier
void	print_builtin_error(char *builtin, char *arg, t_ms *mini)
{
	mini->exit_status = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(builtin, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
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

	i = 0;
	if (!str)
		return (0);
	if (str[0] != '_' && !ft_isalpha(str[0]))
		return (0);
	while(str[i] != '\0')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

/* //concatenates two strings while freeing the first one
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
} */
// concatenates two strings while freeing both s1 and s2
char	*ft_strjoin_free_both(char *s1, char *s2)
{
	char *result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		result = ft_strdup(s2);
		free(s2);
		return (result);
	}
	if (!s2)
	{
		result = ft_strdup(s1);
		free(s1);
		return (result);
	}
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

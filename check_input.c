/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 21:10:51 by cacorrea          #+#    #+#             */
/*   Updated: 2025/02/28 21:10:54 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" /*tutto quello commentato non serve 😭*/

/* static int	ft_check_redirection_error(int rd_in, int rd_out)
{
	if (rd_in > 2 || rd_out > 2 || (rd_in > 0 && rd_out > 0))
	{
		ft_putstr_fd("syntax error near unexpected token 😝\n", 2);
		return (0);
	}
	return (1);
}

static int	ft_handle_rd_count(const char *str, int *i, int *rd_in, int *rd_out)
{
	if (str[*i] == '>')
	{
		if (ft_isspace(str[(*i) - 1]) && (*rd_out) > 0)
			(*rd_out)++;
		(*rd_out)++;
	}
	else if (str[*i] == '<')
	{
		if (ft_isspace(str[(*i) - 1]) && (*rd_in) > 0)
			(*rd_in)++;
		(*rd_in)++;
	}
	else if (!ft_isspace(str[*i]))
	{
		if (!ft_check_redirection_error(*rd_in, *rd_out))
			return (0);
		*rd_in = 0;
		*rd_out = 0;
	}
	return (1);
}

static int	ft_isvalid_redirection(const char *str)
{
	int	i;
	int	rd_in;
	int	rd_out;

	i = 0;
	rd_in = 0;
	rd_out = 0;
	while (str[i])
	{
		if (!ft_handle_rd_count(str, &i, &rd_in, &rd_out))
			return (0);
		i++;
	}
	if (rd_in > 0 || rd_out > 0)
	{
		ft_putstr_fd("syntax error near unexpected token 😊\n", 2);
		return (0);
	}
	return (1);
}

static int	ft_isvalid_pipe(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '|' || str[ft_strlen(str) - 1] == '|')
	{
		ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
		return (0);
	}
	while (str[i])
	{
		if (str[i] == '|')
		{
			i++;
			while (str[i] && ft_isspace(str[i]))
				i++;
			if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			{
				ft_putstr_fd("syntax error near unexpected token '|'\n", 2);
				return (0);
			}
		}
		i++;
	}
	return (1);
}*/
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

/*cheks number of quotes, even nb returns 1, odd nb returns 0*/

static int	paired_quotes(const char *str)
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


int	ft_isvalid_input(const char *input)
{
	if (input == NULL || ft_isempty_str(input) || (!paired_quotes(input)))
		return (0);
	return (1);
}

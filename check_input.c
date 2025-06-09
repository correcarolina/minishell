/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 21:10:51 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/09 17:46:47 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" /*tutto quello commentato non serve 😭*/

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
	{
		free((void *)input);
		return (0);
	}	
	return (1);
}

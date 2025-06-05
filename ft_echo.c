/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:05:23 by rd-agost          #+#    #+#             */
/*   Updated: 2025/06/05 20:05:25 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_n_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
	{
		i++;
		if (arg[i] == '\0')
			return (1);
		while (arg[i] != '\0')
		{
			if (arg[i] != 'n')
				return (1);
			i++;
		}
		return (0);
	}
	return (1);
}

int	parse_echo_flags(char **cmd, int *n_flag)
{
	int	i;

	i = 1;
	*n_flag = 0;
	if (!cmd || !cmd[0])
		return (i);
	while (cmd[i] != NULL && ft_n_flag(cmd[i]) == 0)
	{
		*n_flag = 1;
		i++;
	}
	return (i);
}

static int	print_echo_args(char **cmd, int start_index, int n_flag)
{
	int	i;

	i = start_index;
	while (cmd[i] != NULL)
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_flag == 0)
		printf("\n");
	return (0);
}

int	builtin_echo(char **cmd)
{
	int	start_index;
	int	n_flag;

	if (!cmd || !cmd[0])
	{
		printf("\n");
		return (0);
	}
	start_index = parse_echo_flags(cmd, &n_flag);
	return (print_echo_args(cmd, start_index, n_flag));
}

/* int	builtin_echo(char **cmd)
{
	int	i;
	int	n_flag;

	i = 1;
	n_flag = 0;
	if (!cmd || !cmd[0])
	{
		printf("\n");
		return (0);
	}
	while (cmd[i] != NULL)
	{
		if (n_flag != 2 && n_flag != -1 && ft_n_flag(cmd[i]) == 0)
			n_flag = 1;
		else
		{
			printf("%s", cmd[i]);
			if (cmd[i + 1] != NULL)
				printf(" ");
			if (n_flag == 1)
				n_flag = 2;
			if (n_flag == 0)
				n_flag = -1;
		}
		i++;
	}
	if (n_flag <= 0)
		printf("\n");
	return (0);
}
 */
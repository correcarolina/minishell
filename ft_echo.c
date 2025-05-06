/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:05:23 by rd-agost          #+#    #+#             */
/*   Updated: 2025/05/06 19:37:25 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builtin_echo(char **cmd)
{
	int i = 1;
	int n_option = 0;

	if (cmd == NULL ||cmd[0] == NULL)
	{
		printf("\n");
		return;
	}
	if (cmd[i] && strcmp(cmd[i], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
		printf(" ");
		i++;
	}
	if (!n_option)
		printf("\n");
}
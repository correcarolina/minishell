/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:05:23 by rd-agost          #+#    #+#             */
/*   Updated: 2025/04/26 19:02:11 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builtin_echo(t_cmdblock *data)
{
	int i = 1;
	int n_option = 0;

	if (data->cmd == NULL || data->cmd[0] == NULL)
	{
		printf("\n");
		return;
	}
	if (data->cmd[i] && strcmp(data->cmd[i], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	while (data->cmd[i])
	{
		printf("%s", data->cmd[i]);
		if (data->cmd[i + 1])
		printf(" ");
		i++;
	}
	if (!n_option)
		printf("\n");
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:16:35 by rd-agost          #+#    #+#             */
/*   Updated: 2025/04/26 18:58:45 by rd-agost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_matrix(t_envlst **matrix)//la stampa c'e in ft_env
{
	int i;

	i = 0;
	while (matrix[i] != NULL)
	{
		printf("%s=%s\n", matrix[i]->key, matrix[i]->value);
		i++;
	}
}

void execute_command(t_cmdblock *data, t_envlst **env, t_ms *mini)
{
	if (ft_strcmp("echo", data->cmd[0]) == 0)
	builtin_echo(data);
	else if (ft_strcmp("cd", data->cmd[0]) == 0)
	printf("cd\n");
	else if (ft_strcmp("pwd", data->cmd[0]) == 0)
	ft_pwd(mini);
	else if (ft_strcmp("export", data->cmd[0]) == 0)
	ft_export(mini);
	else if (ft_strcmp("unset", data->cmd[0]) == 0)
	printf("unset\n");
/* else if (ft_strcmp("env_matrix", data->command[0]) == 0)
	env_matrix(); */
	else if (ft_strcmp("env", data->cmd[0]) == 0)
	print_matrix(env);

}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:49:27 by cacorrea          #+#    #+#             */
/*   Updated: 2025/02/11 12:49:31 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//unset HOME   cerca se trova HOME (primo arg o arg[1] se arg[0] = unset)
//se lo trova rimove il nodo

void	ft_unset(t_ms	*mini, char *key) //unset e il cmd e key e il primo arg
{
	if (!mini || !mini->myenv || !key)
		return ;
	env_rm_node(&mini->myenv, key);
}

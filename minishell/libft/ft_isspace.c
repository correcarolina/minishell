/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 18:52:33 by cacorrea          #+#    #+#             */
/*   Updated: 2025/01/31 18:52:36 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*checks  for  a space, tab or newline  character, if is space returns 1, 
else returns 0*/

int	ft_isspace(int c)
{
	if (c == 32 || c == 9 || c == 10)
		return (1);
	return (0);
}

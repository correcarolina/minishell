/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:01:11 by cacorrea          #+#    #+#             */
/*   Updated: 2023/12/30 16:01:14 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//convert upercase letters to lowercase

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chartostr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:14:20 by cacorrea          #+#    #+#             */
/*   Updated: 2025/02/17 18:14:26 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_chartostr(int c)
{
	char	*str;

	if (!c)
		return (NULL);
	str = (char *)malloc(2 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = (char)c;
	str[1] = '\0';
	return (str);
}

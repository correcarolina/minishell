/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 08:39:48 by cacorrea          #+#    #+#             */
/*   Updated: 2024/01/26 08:39:51 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates and returns a substring from the string ’s’.
The substring begins at index ’start’ and is of maximum size ’len*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	s_size;
	char			*substr;

	i = 0;
	if (!s)
		return (NULL);
	s_size = (unsigned int)ft_strlen(s);
	if ((s_size < start) || len == 0)
		len = 0;
	else if (len + start > s_size)
		len = s_size - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}

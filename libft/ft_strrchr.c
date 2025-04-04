/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 16:01:51 by cacorrea          #+#    #+#             */
/*   Updated: 2023/12/30 16:01:53 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//returns a pointer to the last occurrence of the character c in the string s

char	*ft_strrchr(const char *s, int c)
{
	const char	*p;

	p = s;
	while (*s)
		s++;
	while (s >= p)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s--;
	}
	return (NULL);
}
/* 
#include <stdio.h>
int	main(void)
{
	const char	str[20] = "feliz ano nuevo";
	int	c = 'n';
	printf("la stringa dall'ultimo char %c e = %s\n", c, ft_strrchr(str, c));
	printf("l'indirizzo puntato e = %p\n", ft_strrchr(str, c));
	printf("l'indirizzo puntato dalla fn originale e = %p\n", strrchr(str, c));
	return (0);
} */

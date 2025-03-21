/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 17:40:58 by cacorrea          #+#    #+#             */
/*   Updated: 2023/12/30 17:41:02 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//compares only the first n bytes of s1 and s2

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((i < n - 1) && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		else
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/* #include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("ft_strncmp = %d", ft_strncmp("test200", "test22", 6));
	printf("\nlibreria = %d", strncmp("test200", "test22", 6));
    printf("\nft_strncmp = %d", ft_strncmp("buon13", "buon12", 6));
	printf("\nlibreria = %d", strncmp("buon13", "buon12", 6));
	printf("\nft_strncmp = %d ", ft_strncmp("ciao", "ciao", 4));
	printf("\nlibreria = %d", strncmp("ciao", "ciao", 4));
	printf("\nft_strncmp = %d ", ft_strncmp("", "Hello", 3));
	printf("\nlibreria = %d", strncmp("", "Hello", 3));
	printf("\nft_strncmp = %d ", ft_strncmp("", "", 1));
	printf("\nlibreria = %d", strncmp("", "", 1));
	return (0);
} */

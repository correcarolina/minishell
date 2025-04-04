/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:26:53 by cacorrea          #+#    #+#             */
/*   Updated: 2023/12/30 18:26:55 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*returns  an  integer  less  than,  equal  to,  or greater than zero if the
  first n bytes of s1 is found, respectively, to be less than, to match, or be
  greater than the first n bytes of s2.*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (p1[i] != p2[i])
			return (p1[i] - p2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
    const char str1[] = "Hello World!";
    const char str2[] = "Hello 42";
    size_t n = 7;
    int result = ft_memcmp(str1, str2, n);

    if (result == 0)
        printf("i primi %zu caracteri delle strings sono uguali\n", n);
    else if (result < 0)
        printf("il primo carattere diverso e piu piccolo in str1 che in str2\n");
    else
        printf("il primo carattere diverso e piu piccolo in str2 che in str1\n");
    return 0;
}*/

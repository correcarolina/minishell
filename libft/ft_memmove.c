/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:28:53 by cacorrea          #+#    #+#             */
/*   Updated: 2023/12/21 09:28:57 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

//function  copies n bytes from memory area src to dest, strings may overleap

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	if (!src && !dest && n > 0)
		return (NULL);
	i = 0;
	d = (char *)dest;
	s = (const char *)src;
	if (src < dest)
	{
		while (n--)
			d[n] = s[n];
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

/* #include <stdio.h>

int main (void) 
{
   char dest[] = "12345";
   const char src[]  = "abc";

   printf("prima di ft_memmove dest = %s, src = %s\n", dest, src);
   ft_memmove(dest, src, 4);
   printf("dopo ft_memmove dest = %s, src = %s\n", dest, src);

   return (0);
} */

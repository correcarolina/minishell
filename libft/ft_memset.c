/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:42:19 by cacorrea          #+#    #+#             */
/*   Updated: 2023/12/18 11:42:22 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//fills the first n bytes of the mem area point by s with the constant byte c

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

/*The c value is passed as an int, but the function fills the block of memory 
using the unsigned char conversion of this value, that's why we need to use a 
pointer to char to fill the memory area */

/* #include <stdio.h>
#include <string.h>

int main () 
{
   char str[50] = "come funziona ft_memset";

   puts(str);
   memset(str,'*',7);
   puts(str);
   ft_memset(str,'w',5);
   puts(str);
   return(0);
} */

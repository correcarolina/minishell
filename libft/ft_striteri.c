/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:01:08 by cacorrea          #+#    #+#             */
/*   Updated: 2024/02/08 18:01:17 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Applies the function ’f’ on each character of the string passed as argument,
  passing its index as first argument. Each character is passed by address to
  ’f’ to be modified if necessary. 
  s: The string on which to iterate.
  f: The function to apply to each character.*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, (s + i));
		i++;
	}
}

/*void	miatest(unsigned int i, char *c)
{
	if (i < 5)
		*c = 'z';
}

int	main (void)
{
	char	str[20] = "hello, world!";
	printf("la stringa originale e: %s\n", str);
	ft_striteri(str, miatest);
	printf("la stringa modificata e: %s\n", str);
	return (0);
}*/

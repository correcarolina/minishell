/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:49:28 by cacorrea          #+#    #+#             */
/*   Updated: 2024/02/08 15:49:32 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Applies the function ’f’ to each character of the string ’s’, and passing its
  index as first argument to create a new string (with malloc(3)) resulting
  from successive applications of ’f’.
  Returns the string created from the successive applications of ’f’ or NULL if
  the allocation fails*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	char			*new;
	unsigned int	i;

	i = 0;
	len = ft_strlen(s);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}

/* char ft_uppercase(unsigned int i, char c)
{
	if (i < 5)
		return ((char)ft_toupper(c));
	else
		return (c);
}

int	main (void)
{
	char const	*str = "ciao mondo";
	printf ("la stringa originale e %s\n", str);
	printf ("la stringa modificata e %s\n", ft_strmapi(str, ft_uppercase));
	return (0);
} */

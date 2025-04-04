/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:58:08 by cacorrea          #+#    #+#             */
/*   Updated: 2024/02/02 10:58:12 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates (with malloc(3)) and returns a string representing the integer 
  received as an argument.  Negative numbers must be handled*/

static unsigned int	ft_len_nb(int nb)
{
	unsigned int	i;

	i = 0;
	if (nb == -2147483648)
		return (11);
	else if (nb == 0)
		return (1);
	else if (nb < 0)
	{
		i++;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static char	*ft_print_min_int(char *str)
{
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	len;

	len = ft_len_nb(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	if (n == -2147483648)
		str = ft_print_min_int(str);
	else if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	else if (n == 0)
		str[0] = '0';
	while (n > 0)
	{
		len--;
		str[len] = (n % 10) + 48;
		n = n / 10;
	}
	return (str);
}
/* 
int	main()
{
	printf("%s\n", ft_itoa(-2147483648));
	return(0);
} */

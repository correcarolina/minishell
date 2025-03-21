/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:06:04 by cacorrea          #+#    #+#             */
/*   Updated: 2024/01/26 10:06:09 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates (with malloc) and returns a copy of ’s1’ with the characters 
specified in ’set’ removed from the beginning and the end of the string*/

static int	ft_search(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len;
	char	*str;

	i = 0;
	j = 0;
	len = ft_strlen(s1);
	if (!s1 || !set)
		return (0);
	while ((s1[i] != '\0') && (ft_search(s1[i], set) != 0))
		i++;
	while (len > i && ft_search(s1[len - 1], set) != 0)
		len--;
	str = (char *)malloc(sizeof(char) * (len - i + 1));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

/* int	main(void)
{
	char const	*s1;
	char const	*set;

	s1 = "www wwzbuona giornata yyyyeah! xyzzz  x";
	set = "wxyz ";
	printf ("%s\n", ft_strtrim(s1, set));
	return (0);
}*/
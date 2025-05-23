/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:07:21 by cacorrea          #+#    #+#             */
/*   Updated: 2024/01/31 12:07:25 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*Allocates (with malloc) and returns an array of strings obtained by splitting 
  ’s’ using the character ’c’ as a delimiter. The array must end with a NULL 
  pointer.  If the allocation fails, returns NULL.*/

static int	ft_countwords(char const *str, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (str[i] != c && str[i] != '\0')
		counter++;
	while (str[i] != '\0')
	{
		if (str[i] == c && str[i + 1] != c && str[i + 1] != '\0')
			counter++;
		i++;
	}
	return (counter);
}

static int	ft_wordlen(char const *str, char c)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (str[i] == c && str[i] != '\0')
		i++;
	while (str[i] != c && str[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char	*ft_newstr(char *str, char c)
{
	int	wl;

	wl = ft_wordlen(str, c);
	str = (char *)ft_calloc((wl + 1), (sizeof(char)));
	if (str == NULL)
		return (NULL);
	return (str);
}

void	ft_free_matrix(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i] != NULL)
	{
		free (strs[i]);
		i++;
	}
	free (strs);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		words;
	int		i;
	int		j;

	i = 0;
	words = ft_countwords(s, c);
	if (!words)
		return (NULL);
	split = (char **)ft_calloc((words + 1), sizeof(char *));
	if (s == NULL || split == NULL)
		return (NULL);
	while (*s != '\0' && i < words)
	{
		j = 0;
		split[i] = ft_newstr((char *)s, c);
		if (split[i] == NULL)
			ft_free_matrix(split);
		while (*s == c && *s != '\0')
			s++;
		while (*s != c && *s != '\0')
			split[i][j++] = *s++;
		i++;
	}
	return (split);
}

/* int	main(void)
{
	int	i = 0;
	char const	s[60] = "   uno due  tre  quattro  ";
	int	wd = ft_countwords(s, ' ');
	char	**s1 = ft_split(s, ' ');
	while (i < wd)
	{
		printf("%s\n", s1[i]);
		i++;
	}
	return (0);
} */

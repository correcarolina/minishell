/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:57:09 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/03 15:56:02 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*returns a pointer to a new string which is a duplicate of the string s.
  Memory for the new string is obtained with malloc, can be freed with free*/

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(s);
	dup = (char *)ft_calloc((len + 1), sizeof(char));
	if (dup == NULL)
		return (NULL);
	ft_strlcpy(dup, s, len + 1);
	return (dup);
}

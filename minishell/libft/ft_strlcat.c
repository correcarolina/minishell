/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 09:29:33 by cacorrea          #+#    #+#             */
/*   Updated: 2023/12/21 09:29:35 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*concatenate strings, takes the full size of the buffer including null-term
  return: len destination + len source*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_dst;
	size_t	len_src;

	j = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = len_dst;
	if (size <= len_dst)
		return (size + len_src);
	while (src[j] != '\0' && (j + i) < (size - 1))
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < size - 1)
		dst[i + j] = '\0';
	return (len_dst + len_src);
}

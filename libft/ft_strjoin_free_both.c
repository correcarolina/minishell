/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_both.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:05:26 by cacorrea          #+#    #+#             */
/*   Updated: 2025/06/03 16:06:36 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// concatenates two strings while freeing both s1 and s2
char	*ft_strjoin_free_both(char *s1, char *s2)
{
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		result = ft_strdup(s2);
		free(s2);
		return (result);
	}
	if (!s2)
	{
		result = ft_strdup(s1);
		free(s1);
		return (result);
	}
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

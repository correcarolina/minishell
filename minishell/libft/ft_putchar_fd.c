/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:55:20 by cacorrea          #+#    #+#             */
/*   Updated: 2024/02/10 17:55:23 by cacorrea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Outputs the character ’c’ to the given file descriptor.

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/* int	main(void)
{
	int	fd;

	fd = open("prove.txt", O_WRONLY);
	ft_putchar_fd('x', fd);
	close(fd);
	return(0);
} */

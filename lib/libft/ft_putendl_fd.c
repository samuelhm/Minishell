/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:18:00 by linyao            #+#    #+#             */
/*   Updated: 2024/06/10 16:41:32 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
//#include <fcntl.h>
//#include <stdio.h>

void	ft_putendl_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
	write(fd, "\n", 1);
}
/*
int	main(void)
{
	int	fd;
	char	s[] = "hello world!";
	
	fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Cannot open file. \n");
		return (1);
	}
	ft_putendl_fd(s, fd);
	close(fd);
	if (fd == -1)
	{
		printf("Cannot close file. \n");
		return (1);
	}
	return (0);
}
*/

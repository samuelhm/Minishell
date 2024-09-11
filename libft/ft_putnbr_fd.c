/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:44:03 by linyao            #+#    #+#             */
/*   Updated: 2024/06/10 18:15:02 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <limits.h>
//#include <stdio.h>
//#include <fcntl.h>

void	ft_putnbr_fd(int n, int fd)
{
	if (n == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}
/*
int	main(void)
{
	int	fd;
	int	n1 = 789456123;
	int	n2 = INT_MIN;
	int	n3 = INT_MAX;
	int	n4 = 0;
	int	n5 = -981256;

	fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Cannot open file. \n");
		return(1);
	}
	ft_putnbr_fd(n1, fd);
	ft_putnbr_fd(n2, fd);
	ft_putnbr_fd(n3, fd);
        ft_putnbr_fd(n4, fd);
	ft_putnbr_fd(n5, fd);
	return (0);
}
*/

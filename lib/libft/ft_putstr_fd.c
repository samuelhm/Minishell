/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:39:59 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 15:08:58 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
//#include <fcntl.h>

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}
/*
int main(void)
{
    int     fd;
    char    s[] = "Hello World";

    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        ft_putstr_fd("Cannot open file.\n", 2);
        return(1);
    }
    ft_putstr_fd(s, fd);
    close(fd);
    if (fd == -1)
    {
        ft_putstr_fd("Cannot close file.\n", 2);
        return(1);
    }
    return (0);
}
*/
// 把字符串s写入给定的文件描述符的文件中

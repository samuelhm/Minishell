/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:06:08 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 15:08:10 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
//#include <fcntl.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
/*
void    ft_putstr_fd(int fd, char *str)
{
    while (*str)
        write(fd, str++, 1);
}

int main(void)
{
    int         fd;
    char        c = 'a';

    fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        ft_putstr_fd(2, "Cannot open file.\n");
        return(1);
    }
    ft_putchar_fd(c, fd);
    close(fd);
    if (fd == -1)
    {
        ft_putstr_fd(2, "Cannot close file.\n");
        return(1);
    }
    return (0);
}
*/
// 把字符c写入给定的文件描述符的文件中

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:16:27 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 17:23:05 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <unistd.h>
//#include <ctype.h>

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/*
int main(void)
{
    char s[] = "Hello world!";
    int i = 0;
    char    c;

    while (s[i])
    {
        c = ft_toupper((unsigned char)s[i]);
        write (1, &c, 1);
        i++;
    }
    write (1, "\n", 1);
    return (0);
}
*/

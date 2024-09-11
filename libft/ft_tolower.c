/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:48:28 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 17:22:18 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <unistd.h>

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}
/*
int main(void)
{
    char s[] = "Hello World!";
    int i = 0;
    char    c;

    while (s[i])
    {
        c = ft_tolower((unsigned char)s[i]);
        write (1, &c, 1);
        i++;
    }
    write (1, "\n", 1);
    return (0);
}
*/

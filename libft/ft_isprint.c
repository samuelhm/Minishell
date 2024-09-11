/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:33:21 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 14:35:06 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <ctype.h>

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
/*
int main(void)
{
    char    a = '~';
    char    b = '\n';
    char    c = ' ';

    printf ("%d\n", ft_isprint(a));
    printf ("%d\n", isprint(a));
    printf ("%d\n", ft_isprint(b));
    printf ("%d\n", isprint(b));
    printf ("%d\n", ft_isprint(c));
    printf ("%d\n", isprint(c));
    return (0);
}
*/

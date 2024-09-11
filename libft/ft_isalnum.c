/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:24:23 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 14:29:55 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <ctype.h>

int	ft_isalnum(int c)
{
	if ((c <= '9' && c >= '0')
		|| (c <= 'z' && c >= 'a')
		|| (c <= 'Z' && c >= 'A'))
		return (1);
	return (0);
}
/*
int main(void)
{
    char    a = '2';
    char    b = 'a';
    char    c = 'T';
    char    d = '@';

    printf("%d\n", ft_isalnum(a));
    printf("%d\n", isalnum(a));
    printf("%d\n", ft_isalnum(b));
    printf("%d\n", isalnum(b));
    printf("%d\n", ft_isalnum(c));
    printf("%d\n", isalnum(c));
    printf("%d\n", ft_isalnum(d));
    printf("%d\n", isalnum(d));
    return (0);
}
*/

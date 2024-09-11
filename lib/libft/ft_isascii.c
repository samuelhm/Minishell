/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:03:08 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 14:32:56 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <ctype.h>

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
int main(void)
{
    char    a = 'x';
    char    *b = "â";

    printf("%d\n", ft_isascii(a));
    printf("%d\n", isascii(a));
    printf("%d\n", ft_isascii(b[0]));
    printf("%d\n", isascii(b[0]));
    return (0);
}
*/

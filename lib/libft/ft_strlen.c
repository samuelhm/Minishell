/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 21:45:57 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 17:29:48 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <string.h>
//#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}
/*
int main(void)
{
    const char  *s1;
    const char  *s2;

    s1 = "";
    s2 = "Hello World!";
    printf ("%zu\n", ft_strlen(s1));
    printf ("%zu\n", strlen(s1));
    printf ("%zu\n", ft_strlen(s2));
    printf ("%zu\n", strlen(s2));
    return (0);
}
*/

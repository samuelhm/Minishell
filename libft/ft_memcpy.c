/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:41:31 by linyao            #+#    #+#             */
/*   Updated: 2024/06/14 20:12:37 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/*
int main(void)
{
    char    src[] = "Hello World!";
    char    dest[50] = {0};
    char    src1[] = "Hello World!";
    char    dest1[50] = {0};

    ft_memcpy(dest, src, 8);
    dest[8] = '\0';
    memcpy(dest1, src1, 8);
    dest1[8] = '\0';
    printf("src: %s\n", src);
    printf("dest: %s\n", dest);
    printf("src1: %s\n", src1);
    printf("dest1: %s\n", dest1);
    return (0);
}
*/

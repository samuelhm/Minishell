/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:56:23 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 15:47:00 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		srclen;
	const char	*s;

	srclen = 0;
	s = src;
	while (*s++)
		srclen++;
	if (dstsize == 0)
		return (srclen);
	i = 0;
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (srclen);
}
/*
int main(void)
{
    char src[] = "Hello, World!";
    char dest[20];
    size_t cpynum = ft_strlcpy(dest, src, sizeof(dest));
    char src1[] = "Hello, World!";
    char dest1[20];
    size_t cpynum1 = strlcpy(dest1, src1, sizeof(dest1));

    printf("Copied string: %s\n", dest);
    printf("Length of src: %zu\n", cpynum);
    printf("Copied string1: %s\n", dest1);
    printf("Length of src1: %zu\n", cpynum1);
    return 0;
}
*/

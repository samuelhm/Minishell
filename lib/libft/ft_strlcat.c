/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:30:03 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 17:28:25 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;

	dst_len = 0;
	i = 0;
	src_len = ft_strlen(src);
	while (dst_len < dstsize && dst[dst_len] != '\0')
		dst_len++;
	if (dst_len == dstsize)
		return (dst_len + src_len);
	while ((i < dstsize - dst_len - 1) && src[i] != '\0')
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
/*
int main(void)
{
    char    dst[20] = "Hello";
    char    src[] = " World!";
    char    dst1[20] = "Hello";
    char    src1[] = " World!";
    size_t  dstsize = sizeof(dst);
    size_t  dstsize1 = sizeof(dst1);
    size_t  result = ft_strlcat(dst, src, dstsize - 16);
    size_t  result1 = strlcat(dst1, src1, dstsize1 - 16);
    printf("DstSize: %zu\n", dstsize);
    printf("Resulting string: %s\n", dst);
    printf("Length: %zu\n", result);
    printf("Resulting string1: %s\n", dst1);
    printf("Length1: %zu\n", result1);
    return (0);
}
*/

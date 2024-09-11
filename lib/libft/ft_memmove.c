/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:49:24 by linyao            #+#    #+#             */
/*   Updated: 2024/06/14 20:15:28 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (s < d && d < s + n)
	{
		d += n;
		s += n;
		while (n--)
			*(--d) = *(--s);
	}
	else
	{
		while (n--)
			*(d++) = *(s++);
	}
	return (dest);
}
/*
int main(void)
{
    char    src[] = "Hello World!";
    char    dest[20];
    char    overlap[] = "abcdefgh";
    char    src1[] = "Hello World!";
    char    dest1[20];
    char    overlap1[] = "abcdefgh";

    ft_memmove(dest, src, 15); // n表示要复制的字节数，而不是数组的元素个数
    ft_memmove(overlap + 2, overlap, 4);
    // n由调用者负责正确提供
    // 如果n超过源数组或目标数组实际大小，这是调用者责任，会导致未定义行为
    // memmove函数不处理n超过源或目标数组大小的情况
    memmove(dest1, src1, 15);
    memmove(overlap1 + 2, overlap1, 4);
    printf("src: %s\n", src);
    printf("dest: %s\n", dest);
    printf("src1: %s\n", src1);
    printf("dest1: %s\n", dest1);
    printf("overlap: %s\n", overlap);
    printf("overlap1: %s\n", overlap1);
    printf("overlap+2: %s\n", overlap + 2);
    printf("overlap1+2: %s\n", overlap1 + 2);
    return (0);
}
*/
//如果src在dest前面，有内存重叠，则从后往前复制
//    if (s < d && d < s + n)
//    else //src在dest前且无重叠，或者src在dest后不管有无重叠，都从前往后复制
//    {
//        while (n--)
//            *(d++) = *(s++);
//    }

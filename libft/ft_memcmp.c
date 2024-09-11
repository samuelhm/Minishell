/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 23:33:52 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 14:54:05 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	while (n--)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (0);
}
/*
int main(void)
{
    const char str1[] = "Hello, World!";
    const char str2[] = "Hello, World!";
    const char str3[] = "Hello, Wxrld!";
    
    int result1 = ft_memcmp(str1, str2, strlen(str1));
    int result2 = ft_memcmp(str1, str3, strlen(str1));
    int result3 = memcmp(str1, str2, strlen(str1));
    int result4 = memcmp(str1, str3, strlen(str1));

    printf("Comparison result1 between str1 and str2: %d\n", result1);
    printf("Comparison result2 between str1 and str3: %d\n", result2);
    printf("Comparison result3 between str1 and str2: %d\n", result3);
    printf("Comparison result4 between str1 and str3: %d\n", result4);
    return 0;
}
*/
// 逐字节比较两个内存区域s1和s2的前n个字节，根据比较结果返回一个整数
// 注：这是逐字节比较，常用于比较二进制数据或非字符串数据，它不会在遇到空字符 '\0' 时停止

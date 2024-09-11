/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 23:08:02 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 14:52:07 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		ch;

	ptr = (const unsigned char *)s;
	ch = (unsigned char)c;
	while (n--)
	{
		if (*ptr == ch)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}
/*
int main(void)
{
    const char str[] = "Hello, World!";
    char ch = 'e';
    const char str1[] = "Hello, World!";
    char ch1 = 'e';
    char *result = ft_memchr(str, ch, strlen(str));
    char *result1 = memchr(str1, ch1, strlen(str1));

    if (result != NULL) {
        printf("Character '%c' found at position: %ld\n", ch, result - str);
    } else {
        printf("Character '%c' not found.\n", ch);
    }
    if (result1 != NULL) {
        printf("Character '%c' found at position: %ld\n", ch1, result1 - str1);
    } else {
        printf("Character '%c' not found.\n", ch1);
    }
    return 0;
}
*/
// 在给定的内存块s中查找第一次出现的特定字符c，n是要检查的字节数
// 如找到，返回指向首次出现的字符的指针，如未找到，返回 NULL
// c是要查找的字符，作为 int 传递，但该值将转换为 unsigned char

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:11:11 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 17:12:51 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (!*needle)
		return ((char *)haystack);
	if (!*haystack || len == 0)
		return (NULL);
	i = 0;
	while (haystack[i] != '\0' && needle[i] != '\0'
		&& i < len && haystack[i] == needle[i])
		i++;
	if (needle[i] == '\0')
		return ((char *)haystack);
	return (ft_strnstr(haystack + 1, needle, len - 1));
}
/*
int main(void)
{
    const char *haystack = "Hello, World!";
    const char *needle = "llo, Wo";
    size_t len = 10;
    char *result = ft_strnstr(haystack, needle, len);
    char *result1 = strnstr(haystack, needle, len);

    if (result) {
        printf("Found '%s' in 1st %zu characters: %s\n", needle, len, result);
    } else {
        printf("'%s' not found in the first %zu characters\n", needle, len);
    }
    if (result1) {
        printf("Found '%s' in 1st %zu characters: %s\n", needle, len, result1);
    } else {
        printf("'%s' not found in the first %zu characters\n", needle, len);
    }
    return 0;
}
*/
// 该函数用于在字符串haystack的前n个字符中查找另一个子字符串needle
// len是在 haystack 中搜索的最大字符数
// ft_strnstr函数尝试在haystack的前 len 个字符中找到子字符串needle出现的第一个位置
// 如找到，返回指向 haystack 中这个位置的指针；如果未找到，返回 NULL

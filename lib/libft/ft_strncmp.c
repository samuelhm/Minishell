/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 22:41:51 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 17:05:48 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	if (i < n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}
	return (0);
}
/*
int main(void)
 {
    const char *s1 = "Hello, World!";
    const char *s2 = "Hello, World!";
    const char *s3 = "Hello, C Programming!";
    
    printf("Comparing s1 and s2: %d\n", ft_strncmp(s1, s2, 5));  // Output: 0
    printf("Comparing s1 and s2: %d\n", strncmp(s1, s2, 5));
    printf("Comparing s1 and s3: %d\n", ft_strncmp(s1, s3, 6));  // Output: 0
    printf("Comparing s1 and s3: %d\n", strncmp(s1, s3, 6));
    printf("Comparing s1 and s3: %d\n", ft_strncmp(s1, s3, 10)); 
// Output: difference in characters
    printf("Comparing s1 and s3: %d\n", strncmp(s1, s3, 10));
    return 0;
 }
*/
// 此函数用于比较两个字符串的前n个字符是否相等。
// 返回str1-str2的差值。

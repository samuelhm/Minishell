/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:00:23 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 15:23:38 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

char	*ft_strchr(const char *str, int c)
{
	while (*str != '\0' && *str != (char)c)
		str++;
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}
/*
int main(void)
{
    const char *str = "Hello, World!";
    char ch = 'o';
    char *result = ft_strchr(str, ch);
    const char *str1 = "Hello, World!";
    char ch1 = 'o';
    char *result1 = strchr(str1, ch1);

    if (result) 
        printf("Character '%c' found at position: %ld\n", ch, result - str);
    else
        printf("Character '%c' not found.\n", ch);
    if (result1) 
        printf("Character '%c' found at position: %ld\n", ch1, result1 - str1);
    else
        printf("Character '%c' not found.\n", ch1);
    return 0;
}
*/
// 在字符串str中寻找字符c，返回c所在的位置。没找到返回NULL

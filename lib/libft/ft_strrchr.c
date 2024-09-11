/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:20:18 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 17:14:43 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = (int)ft_strlen(str);
	while (i >= 0 && str[i] != (char)c)
		i--;
	if (str[i] == (char)c)
		return ((char *)(str + i));
	return (NULL);
}
/*
int main(void)
{
    const char *str = "Hello, World!";
    char ch = 'l';
    char *result = ft_strrchr(str, ch);
    const char *str1 = "Hello, World!";
    char ch1 = 'l';
    char *result1 = strrchr(str1, ch1);
    // main中的str指针位置没有变化，ft_strrchar函数中的str位置变了，但它是函数内部局部变量
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

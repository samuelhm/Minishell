/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:23:26 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 16:20:31 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*result;

	if (!s || !f)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*
char    ft_example(unsigned int index, char c)
{
    return(c + index % 26);
}

int main(void)
{
    char const  *s = "Hello World!";
    char        *res;

    res = ft_strmapi(s, ft_example);
    printf("Original: %s\n", s);
    printf("Result:%s\n", res);
    return(0);
}
*/
// 该函数将f应用于字符串s的每个字符，并将其索引作为第一个参数，字符本身作为第二个参数
// 返回的新字符串使用 malloc 创建以收集 f 的结果

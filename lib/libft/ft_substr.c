/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:28:43 by linyao            #+#    #+#             */
/*   Updated: 2024/10/08 11:21:28 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start])
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

/*
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
	{
		str = (char *)malloc(sizeof(char));
		if (str != NULL)
			str[0] = '\0';
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
*/
/*
{
	size_t	i;
	size_t	j;
	char	*sub_str;

	sub_str = (char *)malloc((len + 1) * sizeof(char));
	if (!sub_str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			sub_str[j] = s[i];
			j++;
		}
		i++;
	}
	sub_str[j] = 0;
	return (sub_str);
}
*/
/*
int main(void)
{
    char const  *s = "Hello World!";
    char        *sub;

    sub = ft_substr(s, 3, 8);
    printf("substring: %s\n", sub);
    return (0);
}
*/
// 在字符串s中寻找返回子字符串，start是子串开始那个字符在s中的索引位置
// len是该子字符串的最大长
// 如果子字符串起始位置在源字符串的'\0'或之后，返回NULL
//    if (start >= s_len)
//        return (NULL);

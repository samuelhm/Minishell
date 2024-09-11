/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:01:23 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 18:20:33 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len1)
		result[i] = s1[i];
	j = 0;
	while (j < len2)
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}

/*
int main(void)
{
    char const    *s1 = "Hello ";
    char const   *s2 = "World!";
    char    *st = ft_strjoin(s1, s2);

    printf("concatenated: %s\n", st);
    return (0);
}
*/
// 将 s2 字符串添加到 s1 字符串后，并返回合并后的新字符串
// 如果内存分配失败或 s1 或 s2 为空，则返回 NULL

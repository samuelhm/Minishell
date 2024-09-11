/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:41:40 by linyao            #+#    #+#             */
/*   Updated: 2024/06/16 16:26:14 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	**ft_free_array(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && arr[i] != NULL)
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
	return (NULL);
}

size_t	ft_susbtr_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s == c)
		s++;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

size_t	ft_count_substr(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	sub_count;
	size_t	i;

	sub_count = ft_count_substr(s, c);
	array = ft_calloc(sub_count + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (*s && i < sub_count)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			array[i] = ft_substr(s, 0, ft_susbtr_len(s, c));
			if (array[i++] == NULL)
				return (ft_free_array(array, i));
		}
		while (*s && *s != c)
			s++;
	}
	array[sub_count] = NULL;
	return (array);
}
/*
static int	ft_count_substr(const char *str, char c)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (*str)
	{
		if (*str != c && flag == 0)
		{
			flag = 1;
			i++;
		}
		else if (*str == c)
			flag = 0;
		str++;
	}
	return (i);
}

static char	*ft_substr_dup(const char *str, int begin, int end)
{
	char	*sub_str;
	int		i;

	i = 0;
	sub_str = malloc((end - begin + 1) * sizeof(char));
	while (begin < end)
		sub_str[i++] = str[begin++];
	sub_str[i] = '\0';
	return (sub_str);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	int		index;
	char	**array;

	array = malloc((ft_count_substr(s, c) + 1) * sizeof(char *));
	if (!s || !array)
		return (0);
	i = 0;
	j = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			array[j++] = ft_substr_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	array[j] = 0;
	return (array);
}
*/
/*
// 计算要分割的子字符串substrings的个数
static size_t	ft_sub_count(char const *s, char c)
{
	size_t	i;
	size_t	num;

	if (!s || c == '\0')
		return (1);
	i = 0;
	num = 0;
	while (s[i] == c)
		i++;
	if (s[i] != c && s[i] != '\0')
		num = 1;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			num += 1;
		i++;
	}
	return (num);
}

// 计算具体的子字符串中的字符个数
static size_t	ft_sub_len(char const *s, size_t i, char c)
{
	size_t	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	array_index;
	size_t	i;

	if (!s)
		return (NULL);
	if (c == '\0')
	{
		array = (char **)ft_calloc(2, sizeof(char *));
		if (!array)
			return (NULL);
		array[0] = ft_strdup(s);
		return (array);
	}
	array = (char **)ft_calloc((ft_sub_count(s, c) + 1), sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	array_index = 0;
	while (array_index < ft_sub_count(s, c))
	{
		while (s[i] == c)
			i++;
		array[array_index] = ft_substr(s, i, ft_sub_len(s, i, c));
		i += ft_sub_len(s, i, c);
		array_index++;
	}
	return (array);
}
*/
/*
int main(void)
{
    char const  *s = "aaaxyza782a9e";
    char        c = '\0';
    size_t      j = 0;
    
    printf("%zu\n", ft_sub_count(s, c));
    printf("%zu\n", ft_sub_len(s, 11, c));
    while (j < ft_sub_count(s, c))
    {
        printf("%s\n", ft_split(s, c)[j]);
        j++;
    }
    return (0);
}
// sub_len = ft_sub_len(s, i, c);
*/

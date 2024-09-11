/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 22:24:55 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 14:49:34 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h> 
//#include <stdio.h>

static int	int_length(int n)
{
	int	length;

	length = 0;
	if (n <= 0)
		length = 1;
	while (n != 0)
	{
		length++;
		n /= 10;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	int		num;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = int_length(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	num = n;
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	while (num > 0)
	{
		str[--len] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}
/*
int main(void)
{
    int num = -123456;
    int num1 = 0;
    int num2 = INT_MIN;
    int num3 = 789;
    char    *a = ft_itoa(num);
    char    *b = ft_itoa(num1);
    char    *c = ft_itoa(num2);
    char    *d = ft_itoa(num3);

    if (a)
    {
        printf("%s\n", a);
        free(a);
    }
    if (b)
    {
        printf("%s\n", b);
        free(b);
    }
    if (c)
    {
        printf("%s\n", c);
        free(c);
    }
    if (d)
    {
        printf("%s\n", d);
        free(d);
    }
    return (0);
}
*/

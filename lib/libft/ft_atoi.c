/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:37:11 by linyao            #+#    #+#             */
/*   Updated: 2024/06/12 15:29:21 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <stdlib.h>

int	ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return ((int)(sign * result));
}
/*
int main(void)
{
    const char  *s = "  -123a456adc";
    int n = ft_atoi(s);
    printf("%d\n", n);
    const char  *s1 = "  -123a456adc";
    int n1 = atoi(s1);
    printf("%d\n", n1);
    return (0);
}
*/
// 该函数和atoi一模一样，只判断第一个加减号，如有多个加减号，结果返回0
// 该函数和atoi一样，不处理大于INT_MAX和小于INT_MIN的溢出问题

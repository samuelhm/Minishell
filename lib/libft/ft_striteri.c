/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:02:30 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 15:30:35 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void    ft_exam(unsigned int i, char *c)
{
    *c =  *c + i % 26;
}

int main(void)
{
    char    s[] = "Hello, World!";

    ft_striteri(s, ft_exam);
    printf("Modified: %s\n", s);
    return(0);
}
*/

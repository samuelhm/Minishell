/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:54:02 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 14:21:53 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>
//#include <strings.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
/*
int main(void)
{
    char    buffer1[10];
    char    buffer2[10];
    size_t  i;

    ft_memset(buffer1, 'B', 10);
    memset(buffer2, 'B', 10);
    for (i = 0; i < sizeof(buffer1); i++) 
    {
        printf("%d ", buffer1[i]);
    }
    printf("\n");
    for (i = 0; i < sizeof(buffer2); i++) 
    {
        printf("%d ", buffer2[i]);
    }
    printf("\n");
    ft_bzero(buffer1, 6);
    bzero(buffer2, 6);
    for (i = 0; i < sizeof(buffer1); i++) 
    {
        printf("%d ", buffer1[i]);
    }
    printf("\n");
    for (i = 0; i < sizeof(buffer2); i++) 
    {
        printf("%d ", buffer2[i]);
    }
    printf("\n");
    return (0);
}
*/

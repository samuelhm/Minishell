/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:11:01 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 15:07:08 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>
//#include <string.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
int main(void)
{
    char    buffer1[20];
    char    buffer2[20];
    size_t  i;

    ft_memset(buffer1, 0, sizeof(buffer1));
    memset(buffer2, 0, sizeof(buffer2));
    printf("%s\n", buffer1);
    printf("%s\n", buffer2);
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
    ft_memset(buffer1, 'A', 10);
    memset(buffer2, 'A', 10);
    printf("%s\n", buffer1);
    printf("%s\n", buffer2);
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

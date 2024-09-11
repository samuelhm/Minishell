/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:31:20 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 14:26:12 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdlib.h>
//#include <stdio.h>

void	*ft_calloc(size_t num, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = num * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}
/*
int main (void)
{
    int *array;
    size_t  num_elements = 10;

    array = ft_calloc(num_elements, sizeof(int));
    if (!array)
    {
        printf("Memory allocation failed\n");
        return 1;
    }
//  for (size_t i = 0; i < (num_elements * sizeof(int)); i++)
    for (size_t i = 0; i < num_elements; i++)
        printf("%d ", array[i]);
    printf("\n");
    free (array);
    return (0);
}
*/
// 注意：该函数要初始化每个字节，所以传入memset的参数是总字节数

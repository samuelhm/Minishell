/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 21:53:00 by linyao            #+#    #+#             */
/*   Updated: 2024/06/13 17:25:04 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
/*
int main(void)
{
    char    *s = "hello world!";
    t_list  *node;

    node = ft_lstnew(s);
    if (node)
    {
        printf("Node content: %s\n", (char *)node->content);
        printf("Node next: %p\n", (void *)node->next);
    }
    else
        printf("Memory allocation failed\n");
    free(node);
    return(0);
}
*/
// 该函数使用 malloc 分配内存，并返回一个新的链表节点
// 链表节点的 content 成员变量被初始化为传递给函数的参数值
// next 成员变量被初始化为 NULL

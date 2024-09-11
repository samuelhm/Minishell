/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:54:36 by linyao            #+#    #+#             */
/*   Updated: 2024/06/21 13:39:11 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst && del)
	{
		del (lst->content);
		free (lst);
	}
}

void	del_content(void *content)
{
	free (content);
}
/*
int main(void)
{
    // 创建一个节点并分配内存给节点内容
    char *content = ft_strdup("Node content");
    t_list *node = ft_lstnew(content);

    if (node)
    {
        printf("Before deletion: %s\n", (char *)node->content);
        ft_lstdelone(node, del_content);  // 删除节点
    }

    // 尝试访问已删除的节点（会导致未定义行为）
		printf("After deletion: %d\n", (node == NULL));
    return 0;
}
*/

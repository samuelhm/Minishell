/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:14:45 by linyao            #+#    #+#             */
/*   Updated: 2024/06/11 16:56:58 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*
int	main(void)
{
	t_list	*head;
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;

	char	*content1 = "Hello world!";
	char	*content2 = "42";
	char	*content3 = "Barcelona";
	head = NULL;
	node1 = ft_lstnew(content1);
	node2 = ft_lstnew(content2);
	node3 = ft_lstnew(content3);
	ft_lstadd_front(&head, node1);
	ft_lstadd_front(&head, node3);
	ft_lstadd_front(&head, node2);
	printf("size of list: %d\n", ft_lstsize(head));
	t_list	*current = head;
	while (current)
	{
		printf("Node content: %s\n", (char *)current->content);
		current = current->next;
	}
	while (head)
	{
		t_list	*temp = head;
		head = head->next;
		free(temp);
	}
	return (0);
}
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:03:31 by linyao            #+#    #+#             */
/*   Updated: 2024/06/11 16:11:41 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new)
	{
		new->next = *lst;
		*lst = new;
	}
}
/*
int	main(void)
{
	t_list	*head;
	t_list	*new_node1;
	t_list	*new_node2;
	char	*content1 = "hello, world!";
	char	*content2 = "42";
	new_node1 = ft_lstnew(content1);
	new_node2 = ft_lstnew(content2);
	head = NULL;
	ft_lstadd_front(&head, new_node1);
	ft_lstadd_front(&head, new_node2);
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

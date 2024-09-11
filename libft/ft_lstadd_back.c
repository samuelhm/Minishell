/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 18:22:41 by linyao            #+#    #+#             */
/*   Updated: 2024/06/16 15:41:49 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		current = ft_lstlast(*lst);
		current->next = new;
	}
}
/*
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}
*/
/*
int	main(void)
{
	t_list	*head;
	t_list	*new_node1;
	t_list	*new_node2;

	char	*contenthead = "0 node";
	char	*content1 = "1st node";
	char	*content2 = "2nd node";
	head = ft_lstnew(contenthead);
	new_node1 = ft_lstnew(content1);
	new_node2 = ft_lstnew(content2);
	ft_lstadd_back(&head, new_node1);
	ft_lstadd_back(&head, new_node2);
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

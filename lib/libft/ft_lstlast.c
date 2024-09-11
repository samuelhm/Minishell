/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 17:43:34 by linyao            #+#    #+#             */
/*   Updated: 2024/06/11 18:19:12 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
int	main(void)
{
	t_list	node1;
	t_list	node2;
	t_list	node3;

	node1.content = "1st node";
	node1.next = &node2;

	node2.content = "2nd node";
	node2.next = &node3;

	node3.content = "3rd node";
	node3.next = NULL;

	if (ft_lstlast(&node1))
		printf("Last node content: %s\n", (char *)ft_lstlast(&node1)->content);
	return (0);
}
*/

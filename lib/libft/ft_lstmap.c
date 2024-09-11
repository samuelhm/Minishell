/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:43:45 by linyao            #+#    #+#             */
/*   Updated: 2024/06/17 12:54:18 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*begin;

	if (!lst || !f || !del)
		return (NULL);
	new_list = ft_lstnew(f(lst->content));
	if (!new_list)
		return (NULL);
	begin = new_list;
	lst = lst->next;
	while (lst)
	{
		new_list->next = ft_lstnew(f(lst->content));
		if (!new_list->next)
		{
			del(new_list->content);
			ft_lstclear(&begin, del);
			return (NULL);
		}
		new_list = new_list->next;
		lst = lst->next;
	}
	new_list->next = NULL;
	return (begin);
}
/*
void	*ft_to_uppercase(void *content)
{
	char	*str = (char *)content;
	char	*new_str = ft_strdup(str);
	if (!new_str)
		return (NULL);
	for (int	i = 0; new_str[i]; i++)
		new_str[i] = ft_toupper(new_str[i]);
	return (new_str);
}

void	ft_delete_content(void * content)
{
	free(content);
}

void	ft_print_list(t_list	*lst)
{
	while (lst)
	{
		printf("%s ->", (char *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}

int	main(void)
{
	t_list	*lst = ft_lstnew(ft_strdup("hello"));
	t_list	*node2 = ft_lstnew(ft_strdup("world"));
	t_list	*node3 = ft_lstnew(ft_strdup("!!"));

	ft_lstadd_back(&lst, node2);
	ft_lstadd_back(&lst, node3);

	t_list	*new_lst = ft_lstmap(lst,ft_to_uppercase, ft_delete_content);
	printf("Original list:\n");
	ft_print_list(lst);
	printf("New list:\n");
	ft_print_list(new_lst);
	ft_lstclear(&lst, ft_delete_content);
	ft_lstclear(&new_lst, ft_delete_content);
	return (0);
}
*/

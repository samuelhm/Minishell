/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:10:06 by linyao            #+#    #+#             */
/*   Updated: 2024/10/21 20:37:55 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	hash_function(char *key)
{
	unsigned int	h;

	h = 0;
	while (key && *key)
		h = h * 31 + *key++;
	return (h % HASH_LEN);
}

t_node	*init_list(void)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->key = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

bool	assign_key_value(t_node *node, char *key, char *value)
{
	if (!node || !key)
		return (false);
	node->key = ft_strdup(key);
	if (!node->key)
		return (false);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = ft_strdup("^");
	if (!node->value)
	{
		free(node->key);
		return (false);
	}
	return (true);
}

bool	add_list(t_node *n, char *key, char *value)
{
	t_node	*new;
	t_node	*cur;

	if (!n || !key)
		return (false);
	if (!n->key)
		return (assign_key_value(n, key, value));
	cur = n;
	new = init_list();
	if (!new)
		return (false);
	if (!assign_key_value(new, key, value))
	{
		free(new);
		return (false);
	}
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return (true);
}

bool	del_list(t_node **n, char *key)
{
	t_node	*cur;
	t_node	*pre;

	if (!n || !key)
		return (false);
	cur = *n;
	pre = NULL;
	if (cur && ft_strcmp(cur->key, key) == 0)
		return (free_node(n, cur));
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			pre->next = cur->next;
			free(cur->key);
			free(cur->value);
			free(cur);
			return (true);
		}
		pre = cur;
		cur = cur->next;
	}
	return (false);
}

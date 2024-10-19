/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:10:06 by linyao            #+#    #+#             */
/*   Updated: 2024/10/19 01:15:13 by shurtado         ###   ########.fr       */
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

bool	add_list(t_node *n, char *key, char *value)
{
	t_node	*new;
	t_node	*cur;

	if (!n)
		return (false);
	if (!n->key)
	{
		n->key = ft_strdup(key);
		if (value)
			n->value = ft_strdup(value);
		else
			n->value = ft_strdup("");
		return (true);
	}
	cur = n;
	new = init_list();
	if (!new)
		return (false);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return (true);
}

bool	del_list(t_node *n, char *key)
{
	t_node	*cur;
	t_node	*pre;

	if (!n || !key)
		return (false);
	cur = n;
	pre = NULL;
	if (ft_strcmp(cur->key, key) == 0)
		return (free_node(&n, cur));
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
		{
			pre->next = cur->next;
			return (free_node(&pre->next, cur));
		}
		pre = cur;
		cur = cur->next;
	}
	return (false);
}

bool	del_hash(t_hash *env, char *key)
{
	int	inx;

	inx = hash_function(key);
	if (!env->slot[inx])
		return (false);
	if (del_list(env->slot[inx], key))
	{
		env->slot[inx] = NULL;
		return (true);
	}
	else
		return (false);
}

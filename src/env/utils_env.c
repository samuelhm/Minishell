/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:10:06 by linyao            #+#    #+#             */
/*   Updated: 2024/09/25 19:56:40 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	hash_function(char *key)
{
	unsigned int	h;

	h = 0;
	while (*key)
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
		n->value = ft_strdup(value);
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
	{
		n = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		return (true);
	}
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

bool	del_hash(t_hash *env, char *key)
{
	int	inx;

	inx = hash_function(key);
	if (!env->slot[inx])
		return (false);
	if (del_list(env->slot[inx], key))
		return (true);
	else
		return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 13:10:06 by linyao            #+#    #+#             */
/*   Updated: 2024/09/14 16:55:54 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

unsigned int	hash_function(char *key)
{
	unsigned int	h;

	h = 0;
	while (*key)
		h = h * 31 + *key++;
	return (h % HASH_LEN);
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
		return ;
	if (del_list(env->slot[inx], key))
		return (true);
	else
		return (false);
}

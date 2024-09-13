/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:10:50 by linyao            #+#    #+#             */
/*   Updated: 2024/09/13 18:08:12 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_hash	*init_hash(void)
{
	t_hash	*new;
	int		i;

	new = malloc(sizeof(t_hash));
	if (!new)
		return (NULL);
	i = 0;
	while (i < HASH_LEN)
	{
		new->slot[i] = NULL;
		i++;
	}
	return (new);
}

t_hash	*assign_hash(t_hash *en, char *key, char *value)
{
	t_hash	*current;
	t_hash	*new;
	int		inx;

	inx = hash_function(key);
	if (lookup_hash(en, key))
		del_hash(en, key);
	current = en;
	new = malloc(sizeof(t_hash));
	if (!new)
		return (NULL);
	if (!en->slot->next)
	while (en->slot)
	{
		if (en->slot[i]->key == key)
			
		en;
	}
}

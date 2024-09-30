/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blt_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:09:48 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/30 16:41:34 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	blt_env(t_hash *env)
{
	int		i;
	t_node	*node;

	i = 0;
	while (i < HASH_LEN)
	{
		node = env->slot[i];
		while (node)
		{
			ft_printf("%s=%s\n", node->key, node->value);
			node = node->next;
		}
		i++;
	}
	return (0);
}

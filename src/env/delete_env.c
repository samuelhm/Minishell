/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:21:45 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/20 21:23:18 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_env(t_hash *env)
{
	int		i;
	t_node	*current;
	t_node	*tmp;

	if (!env)
		return ;
	i = 0;
	while (i < HASH_LEN)
	{
		current = env->slot[i];
		while (current)
		{
			tmp = current;
			current = current->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
		i++;
	}
	free(env);
}

bool	free_node(t_node **n, t_node *cur)
{
	if (!cur || !n)
		return (false);
	*n = cur->next;
	free(cur->key);
	free(cur->value);
	free(cur);
	return (true);
}

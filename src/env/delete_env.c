/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 11:21:45 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/02 11:32:31 by shurtado         ###   ########.fr       */
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
			free(tmp->key);
			free(tmp->value);
			current = current->next;
			free(tmp);
		}
		i++;
	}
	free(env);
}

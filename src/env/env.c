/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:10:50 by linyao            #+#    #+#             */
/*   Updated: 2024/10/21 20:36:47 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*lookup_hash(t_hash *env, char *key)
{
	int		inx;
	t_node	*n;

	inx = hash_function(key);
	if (!env->slot[inx])
		return (NULL);
	n = env->slot[inx];
	while (n)
	{
		if (ft_strcmp(n->key, key) == 0)
			return (n->value);
		n = n->next;
	}
	return (NULL);
}

bool	assign_hash(t_hash *en, char *key, char *value)
{
	int	inx;

	inx = hash_function(key);
	if (lookup_hash(en, key))
		del_hash(en, key);
	if (!en->slot[inx])
	{
		en->slot[inx] = init_list();
		if (!en->slot[inx])
			return (false);
		add_list(en->slot[inx], key, value);
	}
	else
		add_list(en->slot[inx], key, value);
	return (true);
}

void	init_env(t_ms *ms, char **env)
{
	int		i;
	int		key_len;
	char	*key;

	ms->env = init_hash();
	assign_hash(ms->env, "?", "?=0");
	i = 0;
	key_len = 0;
	while (env[i])
	{
		key_len = ft_getinx(env[i], '=');
		if (key_len >= 0)
		{
			key = ft_substr(env[i], 0, key_len);
			assign_hash(ms->env, key, env[i] + key_len + 1);
			free(key);
		}
		i++;
	}
}

bool	del_hash(t_hash *env, char *key)
{
	int	inx;

	inx = hash_function(key);
	if (!env->slot[inx])
		return (false);
	if (del_list(&env->slot[inx], key))
		return (true);
	else
		return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:09:52 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/21 16:53:26 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	blt_export(char **av, t_hash *env)
{
	char	*key;
	char	*value;
	char	*equal_sign;
	int		i;
	t_node	*node;

	i = 0;
	node = NULL;
	if (!av[1])
	{
		while (i < HASH_LEN)
		{
			node = env->slot[i];
			while (node)
			{
				ft_printf("declare -x %s=\"%s\"\n", node->key, node->value);
				node = node->next;
			}
			i++;
		}
		return (0);
	}
	i = 1;
	while (av[i])
	{
		equal_sign = ft_strchr(av[i], '=');
		if (equal_sign)
		{
			key = ft_substr(av[i], 0, equal_sign - av[i]);
			value = ft_strdup(equal_sign + 1);
			if (!key || !value)
				return (1);
			assign_hash(env, key, value);
			free(key);
			free(value);
		}
		else
		{
			key = ft_strdup(av[i]);
			if (!key)
				return (1);
			assign_hash(env, key, "");
		}
		i++;
	}
	return (0);
}

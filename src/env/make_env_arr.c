/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_arr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 11:24:13 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/06 16:21:45 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//return how many nodes exist inside env list
static int	get_lenght(t_hash *env)
{
	t_node	*node;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (i < HASH_LEN)
	{
		node = env->slot[i];
		while (node)
		{
			size++;
			node = node->next;
		}
		i++;
	}
	return (size);
}

//assign memory & data for new env line like user=shurtado from key/value list.
static char	*get_envline(t_node *node)
{
	int		size;
	char	*result;
	int		i;
	int		j;

	size = ft_strlen(node->key) + ft_strlen(node->value) + 2;
	result = ft_calloc(size, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (node->key[i])
	{
		result[i] = node->key[i];
		i++;
		j++;
	}
	result[j++] = '=';
	i = 0;
	while (node->value[i])
		result[j++] = node->value[i++];
	result[j] = '\0';
	return (result);
}

//free array if fail
void	free_env_arr(char **env)
{
	int	i;

	i = 0;
	if (!env || !env[0])
		return ;
	while (env[i])
		free(env[i++]);
	free(env);
}

//Assign memory, and fill bidimensional array as env
char	**get_env_arr(t_hash *env)
{
	char	**raw_env;
	int		i;
	int		size;
	t_node	*node;
	int		j;

	j = 0;
	i = 0;
	size = get_lenght(env);
	raw_env = ft_calloc(size + 1, sizeof(char *));
	if (!raw_env)
		return (NULL);
	while (j < HASH_LEN)
	{
		node = env->slot[j];
		while (node)
		{
			raw_env[i] = get_envline(node);
			if (!raw_env[i])
			{
				free_env_arr(raw_env);
				return (NULL);
			}
			node = node->next;
			i++;
		}
		j++;
	}
	raw_env[i] = NULL;
	return (raw_env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:09:52 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/06 16:23:28 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_exported_vars(t_hash *env)
{
	t_node	*node;
	int		i;

	i = 0;
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

//pair[0] is key, pair[1] is value
static int	assign_single_var(char *arg, t_hash *env)
{
	char	*pair[2];
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		pair[0] = ft_substr(arg, 0, equal_sign - arg);
		pair[1] = ft_strdup(equal_sign + 1);
		if (!pair[0] || !pair[1])
			return (1);
		assign_hash(env, pair[0], pair[1]);
		free(pair[0]);
		free(pair[1]);
	}
	else
	{
		pair[0] = ft_strdup(arg);
		if (!pair[0])
			return (1);
		assign_hash(env, pair[0], "");
		free(pair[0]);
	}
	return (0);
}

static int	assign_export_vars(char **av, t_hash *env)
{
	int		i;
	int		result;

	i = 0;
	while (av[++i])
	{
		result = assign_single_var(av[i], env);
		if (result)
			return (1);
	}
	return (0);
}

int	blt_export(char **av, t_hash *env, char ***crude)
{
	int		result;
	char	**crude_env;

	crude_env = *crude;
	if (!av[1])
		return (print_exported_vars(env));

	result = assign_export_vars(av, env);
	if (!result)
	{
		free_array(crude_env);
		crude_env = get_env_arr(env);
	}
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:09:52 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/16 13:18:20 by shurtado         ###   ########.fr       */
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

bool	check_key(char *arg)
{
	int		i;

	i = 0;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_putstr_fd("Not valid identifier\n", 2);
		return (false);
	}
	while (arg[i++])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			if (arg[i] != '=')
			{
				ft_putstr_fd("Not valid identifier\n", 2);
				return (false);
			}
			else
				break ;
		}
	}
	return (true);
}

//pair[0] is key, pair[1] is value
static int	assign_single_var(char *arg, t_hash *env)
{
	char	*pair[2];
	char	*equal_sign;

	if (!check_key(arg))
		return (1);
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

	if (!av[1])
		return (print_exported_vars(env));
	result = assign_export_vars(av, env);
	if (!result)
	{
		free_array(*crude);
		*crude = get_env_arr(env, 0, 0);
	}
	return (result);
}

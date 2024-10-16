/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 01:24:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/16 16:48:21 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_delimiters(char *av, char delimiter)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (av[i])
	{
		if (av[i] == delimiter)
			count++;
		i++;
	}
	return (count);
}

static char	**allocate_new_av(char **av, int *new_size)
{
	char	**new_av;

	*new_size = count_new_size(av);
	new_av = malloc(sizeof(char *) * (*new_size + 1));
	if (!new_av)
		return (NULL);
	return (new_av);
}

int	count_tokens(char *av, char delimiter)
{
	int	count;

	count = 1;
	while (*av)
	{
		if (*av == delimiter)
			count++;
		av++;
	}
	return (count);
}

static char	**split_and_assign(char **new_av, char *av, char *pos, int *j)
{
	int	token_count;
	int	i;

	i = 0;
	token_count = count_tokens(av, '^');
	while (i < token_count)
	{
		pos = strchr(av, '^');
		if (!pos)
		{
			new_av[*j] = strdup(av);
			if (!new_av[*j])
				return (free_newav(new_av, *j));
			(*j)++;
			break ;
		}
		new_av[*j] = strndup(av, pos - av);
		if (!new_av[*j])
			return (free_newav(new_av, *j));
		(*j)++;
		av = pos + 1;
		i++;
	}
	return (new_av);
}

char	**create_new_av(char **av, int i, int j, int new_size)
{
	char	**new_av;
	char	*pos;

	new_av = allocate_new_av(av, &new_size);
	if (!new_av)
		return (NULL);
	i = 0;
	while (av[i])
	{
		pos = ft_strchr(av[i], '^');
		new_av = split_and_assign(new_av, av[i], pos, &j);
		if (!new_av)
			return (NULL);
		i++;
	}
	new_av[j] = NULL;
	return (new_av);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 01:24:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/16 04:37:11 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_newav(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static char	**allocate_new_av(char **av, int *new_size)
{
	int		i;
	char	*pos;
	char	**new_av;

	i = 0;
	while (av[i])
	{
		pos = strchr(av[i], '^');
		if (pos)
			*new_size += 2;
		else
			*new_size += 1;
		i++;
	}
	new_av = malloc(sizeof(char *) * (*new_size + 1));
	if (!new_av)
		return (NULL);
	return (new_av);
}

static char	**split_and_assign(char **new_av, char *av, char *pos, int *j)
{
	if (!pos)
	{
		new_av[*j] = strdup(av);
		if (!new_av[*j])
			return (free_newav(new_av, *j));
		(*j)++;
	}
	else
	{
		new_av[*j] = strndup(av, pos - av);
		if (!new_av[*j])
			return (free_newav(new_av, *j));
		(*j)++;
		new_av[*j] = strdup(pos + 1);
		if (!new_av[*j])
			return (free_newav(new_av, *j));
		(*j)++;
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
		pos = strchr(av[i], '^');
		new_av = split_and_assign(new_av, av[i], pos, &j);
		if (!new_av)
			return (NULL);
		i++;
	}
	new_av[j] = NULL;
	return (new_av);
}

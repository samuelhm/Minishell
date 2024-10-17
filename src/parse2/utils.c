/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:47:06 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/17 17:38:00 by shurtado         ###   ########.fr       */
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

int	count_new_size(char **av)
{
	int	i;
	int	new_size;

	i = 0;
	new_size = 0;
	while (av[i])
	{
		new_size += count_delimiters(av[i], '^');
		new_size += 1;
		i++;
	}
	return (new_size);
}

bool	is_redirection(char *s)
{
	if (!ft_strcmp(s, "<") || !ft_strcmp(s, "<<") || \
		!ft_strcmp(s, ">") || !ft_strcmp(s, ">>"))
		return (true);
	return (false);
}

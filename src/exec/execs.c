/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:04:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/07 20:05:01 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_av_elements(char **av)
{
	int	count;

	count = 0;
	while (av[count])
		count++;
	return (count);
}

int	find_pipe_position(char **av)
{
	int	i;

	i = 0;
	while (av[i] && strcmp(av[i], PIPE_S) != 0)
		i++;
	return (i);
}

char	**allocate_command_array(int size)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (NULL);
	return (cmd);
}

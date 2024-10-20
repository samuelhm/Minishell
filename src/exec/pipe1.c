/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:17:43 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/18 02:06:07 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_child(char **cmd)
{
	if (!cmd || !cmd[0])
		exit(127);
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found.\n", 22);
	exit(127);
}

void	remove_redirections(char **av)
{
	int		i;
	int		j;

	i = 0;
	while (av[i] && ft_strcmp(av[i], PIPE_S) != 0)
	{
		if (is_special(av[i]))
		{
			j = i;
			free(av[i]);
			free(av[i + 1]);
			while (av[j + 2])
			{
				av[j] = av[j + 2];
				j++;
			}
			av[j] = NULL;
			av[j + 1] = NULL;
		}
		else
			i++;
	}
}

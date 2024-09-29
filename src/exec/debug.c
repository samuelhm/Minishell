/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:27:32 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/29 12:31:53 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_debug(t_ms *ms)
{
	int		i;
	char	**av;

	i = 0;
	av = ms->av;

	while (av[i])
	{
		printf("av[%d]: %s \n", i, av[i]);
		i++;
	}
}

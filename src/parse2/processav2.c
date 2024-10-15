/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processav2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:35:24 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/15 21:43:39 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	all_quote_ok(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!check_p2quotes(av[i]))
			return (false);
		i++;
	}
	return (true);
}

char	**process(char **av)
{
	if (!all_quote_ok(av))
	{
		perror("ERROR, no se aceptan comillas abiertas\n");
		free_array(av);
		return (NULL);
	}

}

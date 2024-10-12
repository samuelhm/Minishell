/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:04:27 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/12 19:44:18 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Check for redirect or pipe
bool	is_special(const char *s)
{
	if (
		!ft_strcmp(s, DOUBLE_MORE) || \
		!ft_strcmp(s, DOUBLE_LESS) || \
		!ft_strcmp(s, MORE_S) || \
		!ft_strcmp(s, LESS_S) || \
		!ft_strcmp(s, PIPE_S))
		return (true);
	return (false);
}

// You should receive **av moving its pointer to echo
//in case you have redirects or pipes

int	blt_echo(char **av)
{
	bool	n;

	n = false;
	if (!av || !av[0])
		return (0);
	av++;
	if (av[0] && !strncmp(av[0], "-n", 2))
	{
		n = true;
		av++;
	}
	while (av[0] && !is_special(av[0]))
	{
		ft_printf("%s", *av);
		if (*(av + 1) && !is_special(*(av + 1)))
			ft_printf(" ");
		av++;
	}
	if (!n)
		ft_printf("\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:04:27 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/06 13:51:38 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Check for redirect or pipe
bool	is_special(const char *s)
{
	if (
		!strncmp(s, DOUBLE_MORE, ft_strlen(s)) || \
		!strncmp(s, DOUBLE_LESS, ft_strlen(s)) || \
		!strncmp(s, MORE_S, ft_strlen(s)) || \
		!strncmp(s, LESS_S, ft_strlen(s)) || \
		!strncmp(s, PIPE_S, ft_strlen(s)))
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

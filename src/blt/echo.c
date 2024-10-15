/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:04:27 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/15 19:19:32 by shurtado         ###   ########.fr       */
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
static bool	all_is_n(const char *s)
{
	int	i;

	i = 1;
	while (s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (true);
	else
		return (false);
}

int	blt_echo(char **av)
{
	bool	n;
	int		j;

	j = 0;
	n = false;
	if (!av || !av[0])
		return (0);
	av++;
	while (av[j] && !strncmp(av[j], "-n", 2))
	{
		if (j == 0 && all_is_n(av[j]))
		{
			n = true;
			j++;
		}
		else if (all_is_n(av[j]))
			j++;
		else
			break ;
	}
	while (av[j])
	{
		ft_printf("%s", av[j]);
		if (av[j + 1])
			ft_printf(" ");
		j++;
	}
	if (!n)
		ft_printf("\n");
	return (0);
}

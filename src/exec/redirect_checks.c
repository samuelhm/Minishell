/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_checks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:59:30 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/26 19:05:06 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_any_redirect(char **av)
{
	return (has_in_redirect(av) || has_out_redirect(av));
}

bool	has_in_redirect(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!ft_strcmp(av[i], MORE_S) || !ft_strcmp(av[i], DOUBLE_MORE))
			return (true);
		i++;
	}
	return (false);
}

bool	has_out_redirect(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!ft_strcmp(av[i], LESS_S) || !ft_strcmp(av[i], DOUBLE_LESS))
			return (true);
		i++;
	}
	return (false);
}

bool	has_pipe(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!ft_strcmp(av[i], PIPE_S))
			return (true);
		i++;
	}
	return (false);
}

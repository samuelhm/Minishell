/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:09:57 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/21 16:53:01 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	blt_unset(char **av, t_hash *env)
{
	int	i;

	i = 1;
	if (av[1])
	{
		ft_printf("unset: not enough arguments\n");
		return (1);
	}

	while (av[i])
	{
		del_hash(env, av[i]);
		i++;
	}
	return (0);
}

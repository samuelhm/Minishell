/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:09:50 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/21 16:19:17 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int blt_exit(char **av)
{
	int	exit_code;

	exit_code = 0;
	if (av[1])
	{
		exit_code = ft_atoi(av[1]);
		if (av[2])
		{
			ft_printf("exit: too many arguments\n");
			return (1);
		}
	}
	ft_printf("exit\n");
	exit(0);
}

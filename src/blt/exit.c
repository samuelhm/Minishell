/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:09:50 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/07 17:29:59 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//temporal (void)exit_code becouse !Werror flag
int	blt_exit(t_ms *ms)
{
	char	**av;
	int		exit_code;

	av = ms->av;
	(void)exit_code;
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
	free_resources(ms);
	ft_printf("exit\n");
	exit(exit_code);
}

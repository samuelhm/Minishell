/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:40:56 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/20 17:07:58 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	blt_exit(char **cmd)
{
	int	result;

	if (cmd[1])
	{
		if (cmd[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
		if (!all_digits(cmd[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (2);
		}
		result = ft_atoi(cmd[1]);
	}
	else
		return (0);
	return (result);
}

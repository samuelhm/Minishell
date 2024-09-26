/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:17:34 by linyao            #+#    #+#             */
/*   Updated: 2024/09/25 20:16:37 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_ms	ms;

	(void)av;
	if (ac != 1)
		return (printf("Incorrect number of argument\n"), 1);
	init_env(&ms, env);
	realize_shell(&ms);
	return (0);
}

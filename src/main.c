/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:17:34 by linyao            #+#    #+#             */
/*   Updated: 2024/09/21 17:06:28 by shurtado         ###   ########.fr       */
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
/*
	for (int i = 0; env[i]; i++)
	{
		input = ft_substr(env[i], 0, ft_getinx(env[i], '='));
		printf("%s~~~~~~ \n",lookup_hash(ms.env, input));
	}
*/
/*
	while (1)
	{
		input = readline(PROMPT);
		if (input && *input)
			add_history(input);
		if (input && ft_strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		printf("%s\n", input);
		free(input);
	}
*/
	return (0);
}

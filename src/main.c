/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:17:34 by linyao            #+#    #+#             */
/*   Updated: 2024/09/13 17:33:05 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_ms	*ms;

	(void)av;
	if (ac != 1)
		return (printf("Incorrect number of argument\n"), 1);
	init_hash();
	ms->env = init_hash();
	assign_hash(ms->env, "?", "?=0");	

	while (1)
	{
		input = readline(PROMPT);
		if (input && *input)
			add_history(input);
		if (input && strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		printf("%s\n", input);
		free(input);
	}
	return (0);
}

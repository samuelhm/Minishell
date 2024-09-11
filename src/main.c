/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:17:34 by linyao            #+#    #+#             */
/*   Updated: 2024/09/12 00:48:24 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	main(int ac, char **av, char **env)
int	main()
{
	char	*input;

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

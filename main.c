/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:17:34 by linyao            #+#    #+#             */
/*   Updated: 2024/09/11 13:01:08 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:37:25 by linyao            #+#    #+#             */
/*   Updated: 2024/09/21 21:32:10 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/env.h"

void	init_ms(t_ms *ms, char **env)
{
	init_env(ms, env);
}

void	realize_shell(t_ms *ms)
{
	char	*input;

	while (1)
	{
		input = readline(PROMPT);
		if (input && *input)
		{
			add_history(input);
			ms->av = split_av(input);
			if (!ms->av)
				continue ;
			free(input);
			input = NULL;
//			ms->av = process_av(ms->av, ms->env);
		}
		if ((input && ft_strcmp(input, "exit") == 0) || !input)
		{
			if (input)
			{
				free(input);
				break ;
			}
			break ;
		}
		printf("%s\n", input);
	}
}


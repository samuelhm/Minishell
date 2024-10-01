/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:37:25 by linyao            #+#    #+#             */
/*   Updated: 2024/10/01 10:03:40 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ms(t_ms *ms, char **env)
{
	init_env(ms, env);
}

void	realize_shell(t_ms *ms)
{
	char	*input;

	while (1)
	{
		init_signals(NORMAL);
		input = readline(PROMPT);
		if (input && *input)
		{
			add_history(input);
			ms->av = split_av(ms->env, input);
			free(input);
			input = NULL;
			if (!ms->av)
				continue ;
			ms->av = process_av(ms->av, ms->env);
			show_debug(ms);
			process_line(ms);
			free_array(ms->av);
		}
		else
		{
			free_array(ms->av);
			//free_env(ms->env);
			ft_printf("exit\n");
			exit(0);
		}
	}
}


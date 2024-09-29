/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:37:25 by linyao            #+#    #+#             */
/*   Updated: 2024/09/29 13:55:58 by shurtado         ###   ########.fr       */
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
			free_array(ms->av);
			//process_line(ms);

//			ms->inf = get_infile_path(&ms->av);
		}
	}
}


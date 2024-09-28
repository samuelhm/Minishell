/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:37:25 by linyao            #+#    #+#             */
/*   Updated: 2024/09/28 12:17:24 by shurtado         ###   ########.fr       */
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
			if (!ms->av)
				continue ;
			free(input);
			input = NULL;
			ms->av = process_av(ms->av, ms->env);
			process_line(ms);

//			ms->inf = get_infile_path(&ms->av);
		}
	}
}


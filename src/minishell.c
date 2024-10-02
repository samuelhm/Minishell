/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:37:25 by linyao            #+#    #+#             */
/*   Updated: 2024/10/02 14:11:29 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ms(t_ms *ms, char **env)
{
	init_env(ms, env);
	ms->crude_env = get_env_arr(ms);
}

void	realize_shell(t_ms *ms)
{
	char	*input;
	int		result;

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
			result = process_line(ms);
			free_array(ms->av);
		}
		else
		{
			free_array(ms->av);
			delete_env(ms->env);
			free_array(ms->crude_env);
			ft_printf("exit\n");
			exit(result);
		}
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:37:25 by linyao            #+#    #+#             */
/*   Updated: 2024/10/04 21:17:23 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ms(t_ms *ms, char **env)
{
	init_env(ms, env);
	ms->crude_env = NULL;
	ms->av = NULL;
	ms->crude_env = get_env_arr(ms);
	ms->fd_pipe = NULL;
}

void	free_resources(t_ms *ms, int result)
{
	if (ms->av)
		free_array(ms->av);
	if (ms->env)
		delete_env(ms->env);
	if (ms->crude_env)
		free_array(ms->crude_env);
	ft_printf("exit\n");
	exit(result);
}

void	realize_shell(t_ms *ms)
{
	char	*input;
	int		result;

	result = 0;
	while (1)
	{
		init_signals();
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
			ms->av = NULL;
			clean_pipes(ms->fd_pipe);
			ms->fd_pipe = NULL;
		}
		else
			free_resources(ms, result);
	}
}

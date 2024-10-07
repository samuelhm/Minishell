/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:37:25 by linyao            #+#    #+#             */
/*   Updated: 2024/10/07 13:35:26 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ms(t_ms *ms, char **env)
{
	init_env(ms, env);
	ms->crude_env = NULL;
	ms->av = NULL;
	ms->crude_env = get_env_arr(ms->env, 0, 0);
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

static int	res_prompt(char *input)
{
	free(input);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return (1);
}

static int	process_input(t_ms *ms, int *result)
{
	char	*input;

	input = readline(PROMPT);
	if (!input)
		free_resources(ms, 0);
	if (!*input)
		return (res_prompt(input));
	add_history(input);
	ms->av = split_av(ms->env, input);
	free(input);
	if (!ms->av)
		return (1);
	ms->av = process_av(ms->av, ms->env);
	if (!strcmp(ms->av[0], "exit"))
	{
		if (ms->av[1])
			*result = ft_atoi(ms->av[1]);
		else
			*result = ms->status;
		free_resources(ms, *result);
	}
	return (*result);
}

void	realize_shell(t_ms *ms)
{
	while (1)
	{
		init_signals(NORMAL);
		if (process_input(ms, &ms->status))
			continue ;
		ms->status = process_line(ms);
		free_array(ms->av);
		ms->av = NULL;
		clean_pipes(ms->fd_pipe);
		ms->fd_pipe = NULL;
	}
}

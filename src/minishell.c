/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:37:25 by linyao            #+#    #+#             */
/*   Updated: 2024/10/21 20:14:07 by shurtado         ###   ########.fr       */
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
	ms->last_pid = 0;
	ms->status = 0;
	ms->pidlst = NULL;
	ms->atty_in = dup(STDIN_FILENO);
	ms->atty_out = dup(STDOUT_FILENO);
}

void	free_resources(t_ms *ms)
{
	if (ms->av)
		free_array(ms->av);
	if (ms->env)
		delete_env(ms->env);
	if (ms->crude_env)
		free_array(ms->crude_env);
	ft_printf("exit\n");
}

static int	res_prompt(char *input)
{
	free(input);
	rl_on_new_line();
	rl_replace_line("", 0);
	return (1);
}

static int	process_input(t_ms *ms)
{
	char	*input;
	char	*trimmed;

	input = readline(PROMPT);
	trimmed = ft_strtrim(input, " \t");
	free (input);
	input = trimmed;
	if (!input)
	{
		free_resources(ms);
		exit(0);
	}
	if (!*input)
		return (res_prompt(input));
	if (!(ft_strnstr(input, "<<", ft_strlen(input))))
		add_history(input);
	ms->av = split_input(input, 0, 0);
	free(input);
	ms->av = process(ms->av, ms->env);
	if (!ms->av || !ms->av[0])
		return (1);
	if (ms->av[0] && !ft_strcmp(ms->av[0], "exit") \
		&& !has_redirection(ms->av, PIPE_S))
		return (check_exit_args(ms));
	return (0);
}

int	realize_shell(t_ms *ms)
{
	while (1)
	{
		init_signals(NORMAL);
		if (process_input(ms))
			continue ;
		ms->status = process_line(ms);
		free_array(ms->av);
		ms->av = NULL;
		clean_pipes(ms->fd_pipe);
		ms->fd_pipe = NULL;
	}
}

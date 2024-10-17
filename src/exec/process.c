/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:43:05 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/17 17:36:41 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_final_command(t_ms *ms, int pipi, char **cmd)
{
	exe_cmd(ms, ms->fd_pipe[pipi - 1][0], STDOUT_FILENO, cmd);
	close(ms->fd_pipe[pipi - 1][0]);
}

void	execute_pipe_segment(t_ms *ms, int pipi, char **cmd)
{
	if (pipi == 0)
	{
		exe_cmd(ms, STDIN_FILENO, ms->fd_pipe[0][1], cmd);
		close(ms->fd_pipe[0][1]);
	}
	else
	{
		exe_cmd(ms, ms->fd_pipe[pipi - 1][0], ms->fd_pipe[pipi][1], cmd);
		close(ms->fd_pipe[pipi - 1][0]);
		close(ms->fd_pipe[pipi][1]);
	}
}

int	execute_piped_commands(t_ms *ms)
{
	int		pipi;
	char	**cmd;
	char	**av;

	av = ms->av;
	pipi = 0;
	cmd = get_cmd(av);
	while (ms->fd_pipe[pipi])
	{
		av += find_pipe_position(av);
		av++;
		execute_pipe_segment(ms, pipi, cmd);
		pipi++;
		free_array(cmd);
		cmd = get_cmd(av);
	}
	execute_final_command(ms, pipi, cmd);
	free_array(cmd);
	return (wait_for_last_process(ms));
}

static bool	sintax_ok(char **av)
{
	int		i;
	char	*special;

	i = 0;
	while (av[i])
	{
		if (is_special(av[i]) && av[i + 1])
		{
			special = av[i];
			if (!(ft_strcmp(av[i], av[i + 1])))
			{
				ft_printf(SINTAXERROR, av[i + 1]);
				return (false);
			}
			if (is_redirection(special) && is_redirection(av[i + 1]))
			{
				ft_printf(SINTAXERROR, av[i + 1]);
				return (false);
			}
		}
		i++;
	}
	return (true);
}

int	process_line(t_ms *ms)
{
	if (!sintax_ok(ms->av))
		return (2);
	if (!has_redirection(ms->av, PIPE_S))
	{
		execute_simple_comand(ms);
		if (!is_builtin(ms->av[0]))
			ms->status = wait_for_last_process(ms);
		return (ms->status);
	}
	init_pipes(ms);
	return (execute_piped_commands(ms));
}

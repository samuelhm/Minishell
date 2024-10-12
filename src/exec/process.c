/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:43:05 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/12 15:37:03 by shurtado         ###   ########.fr       */
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

	pipi = 0;
	cmd = get_cmd(ms);
	while (ms->fd_pipe[pipi])
	{
		execute_pipe_segment(ms, pipi, cmd);
		pipi++;
		free_array(cmd);
		cmd = get_cmd(ms);
	}
	execute_final_command(ms, pipi, cmd);
	free_array(cmd);
	return (wait_for_last_process(ms));
}

int	process_line(t_ms *ms)
{
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

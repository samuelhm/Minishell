/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:43:05 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/21 21:11:05 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_cmd_with_pipes(t_ms *ms, int pip, char **cmd)
{
	if (pip == 0)
	{
		exe_cmd(ms, NULL, ms->fd_pipe[0], cmd);
		close(ms->fd_pipe[0][1]);
	}
	else if (ms->fd_pipe[pip])
	{
		exe_cmd(ms, ms->fd_pipe[pip - 1], ms->fd_pipe[pip], cmd);
		close(ms->fd_pipe[pip - 1][0]);
		close(ms->fd_pipe[pip][1]);
	}
	else
	{
		exe_cmd(ms, ms->fd_pipe[pip - 1], NULL, cmd);
		close(ms->fd_pipe[pip - 1][0]);
	}
}

void	execute_segment(t_ms *ms, int pip, char **cmd)
{
	if (!ms->fd_pipe)
	{
		if (has_builtin(cmd))
			handle_builtin(ms, cmd);
		else
			exe_cmd(ms, NULL, NULL, cmd);
	}
	else
		handle_cmd_with_pipes(ms, pip, cmd);
}

static bool	sintax_ok(char **av)
{
	int		i;
	char	*special;

	i = 0;
	while (av[i])
	{
		if (is_special(av[i]))
		{
			special = av[i];
			if (!av[i + 1] || !ft_strcmp(av[i], av[i + 1]) || \
				(is_redirection(special) && (is_redirection(av[i + 1]) || \
				!strcmp(av[i + 1], PIPE_S))))
			{
				if (av[i + 1])
					ft_printf(SINTAXERROR, av[i + 1]);
				else
					ft_printf(SINTAXERROR, "");
				return (false);
			}
		}
		i++;
	}
	return (true);
}

static int	execute_all(t_ms *ms)
{
	int		pip;
	char	**cmd;
	char	**av;

	av = ms->av;
	pip = 0;
	ms->status = 0;
	while ((ms->fd_pipe && ms->fd_pipe[pip]) || pip == 0)
	{
		cmd = get_cmd(av);
		execute_segment(ms, pip, cmd);
		if (find_pipe_position(av))
			av += find_pipe_position(av);
		if (av && av[0] && !strcmp(av[0], PIPE_S))
			av++;
		pip++;
		free_array(cmd);
	}
	if (pip && ms->fd_pipe)
	{
		cmd = get_cmd(av);
		execute_segment(ms, pip, cmd);
		free_array(cmd);
	}
	return (wait_for_last_process(ms));
}

int	process_line(t_ms *ms)
{
	if (!sintax_ok(ms->av))
		return (2);
	init_pipes(ms);
	make_hdoc_files(ms->av);
	init_signals(CHILD);
	return (execute_all(ms));
}

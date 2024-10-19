/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:43:05 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/19 16:47:09 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_segment(t_ms *ms, int pip, char **cmd)
{
	if (!ms->fd_pipe)
	{
		if (has_builtin(cmd))
		{
			setup_redirections(cmd, STDIN_FILENO, STDOUT_FILENO);
			remove_redirections(cmd);
			ms->status = exec_builtin(cmd, ms->env, &ms->crude_env);
			if (!isatty(STDIN_FILENO))
				dup2(ms->atty_in, STDIN_FILENO);
			if (!isatty(STDOUT_FILENO))
				dup2(ms->atty_out, STDOUT_FILENO);
		}
		else
			exe_cmd(ms, NULL, NULL, cmd);
	}
	else if (pip == 0 && ms->fd_pipe && ms->fd_pipe[0])
	{
		exe_cmd(ms, NULL, ms->fd_pipe[0], cmd);
		close(ms->fd_pipe[0][1]);
	}
	else if (ms->fd_pipe && ms->fd_pipe[pip])
	{
		exe_cmd(ms, ms->fd_pipe[pip - 1], ms->fd_pipe[pip], cmd);
		close(ms->fd_pipe[pip - 1][0]);
		close(ms->fd_pipe[pip][1]);
	}
	else if (!ms->fd_pipe[pip])
	{
		exe_cmd(ms, ms->fd_pipe[pip - 1], NULL, cmd);
		close(ms->fd_pipe[pip - 1][0]);
	}
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
		else if (is_special(av[i]) && !av[i + 1])
		{
			ft_printf(SINTAXERROR);
			return (false);
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

//minishell > << endl cat | ls -la > b | << c
//<<
//endl
//cat
//|
//ls
//-la
//>
//b
//|
//<<
//c

int	process_line(t_ms *ms)
{
	if (!sintax_ok(ms->av))
		return (2);
	init_pipes(ms);
	make_hdoc_files(ms->av);
	init_signals(CHILD);
	return (execute_all(ms));
}

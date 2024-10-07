/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:04:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/07 19:11:23 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_av_elements(char **av)
{
	int	count;

	count = 0;
	while (av[count])
		count++;
	return (count);
}

char	**get_cmd(t_ms *ms, int i, int j)
{
	char	**cmd;
	int		num;

	while (ms->av[i] && strcmp(ms->av[i], PIPE_S) != 0)
		i++;
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (NULL);
	while (j < i)
	{
		cmd[j] = strdup(ms->av[j]);
		j++;
	}
	cmd[j] = NULL;
	if (ms->av[i] && strcmp(ms->av[i], PIPE_S) == 0)
		i++;
	num = 0;
	while (num < i)
	{
		free(ms->av[num]);
		ms->av[num] = NULL;
		num++;
	}
	num = 0;
	while (ms->av[i])
	{
		ms->av[num++] = ms->av[i++];
	}
	ms->av[num] = NULL;
	return (cmd);
}

int	process_line(t_ms *ms)
{
	int		pipi;
	char	**cmd;

	pipi = 0;
	if (!has_redirection(ms->av, PIPE_S))
		execute_simple_comand(ms);
	else
	{
		init_pipes(ms);
		cmd = get_cmd(ms, 0, 0);
		while (ms->fd_pipe[pipi])
		{
			if (pipi == 0)
			{
				exe_cmd(ms, STDIN_FILENO, ms->fd_pipe[0][1], cmd);
				close(ms->fd_pipe[0][1]);
			}
			else if (ms->fd_pipe[pipi] != NULL)
			{
				exe_cmd(ms, ms->fd_pipe[pipi -1][0], ms->fd_pipe[pipi][1], cmd);
				close(ms->fd_pipe[pipi -1][0]);
				close(ms->fd_pipe[pipi][1]);
			}
			pipi++;
			free_array(cmd);
			cmd = get_cmd(ms, 0, 0);
		}
		exe_cmd(ms, ms->fd_pipe[pipi -1][0], STDOUT_FILENO, cmd);
		close(ms->fd_pipe[pipi -1][0]);
		free_array(cmd);
	}
	return (wait_for_last_process(ms));
}

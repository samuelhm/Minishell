/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:41:03 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/04 16:24:04 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_pipes(int **fd_pipe)
{
	int	i;

	i = 0;
	if (fd_pipe)
	{
		while (fd_pipe[i])
		{
			free(fd_pipe[i]);
			i++;
		}
		free(fd_pipe);
	}
}

void	init_pipes(t_ms *ms)
{
	int	i;
	int	pipe_count;

	i = 0;
	pipe_count = 0;
	while (ms->av[i])
	{
		if (!strcmp(ms->av[i], "|"))
			pipe_count++;
		i++;
	}
	ms->fd_pipe = malloc(sizeof(int *) * (pipe_count + 1));
	if (!ms->fd_pipe)
	{
		perror("Error al asignar memoria para pipes");
		return ;
	}
	i = 0;
	while (i < pipe_count)
	{
		ms->fd_pipe[i] = malloc(sizeof(int) * 2);
		if (pipe(ms->fd_pipe[i]) == -1)
		{
			perror("Error creando pipe");
			clean_pipes(ms->fd_pipe);
		}
		i++;
	}
	ms->fd_pipe[pipe_count] = NULL;
}

void	process_pipe(int fd_pipe[2], int is_last, int fd_local[2])
{
	if (!is_last && pipe(fd_pipe) == -1)
		perror("Error at process_pipe");
	if (is_last)
		fd_local[1] = STDOUT_FILENO;
	else
	{
		fd_local[1] = fd_pipe[1];
		fd_local[0] = fd_pipe[0];
	}
}

int	wait_for_last_process(t_ms *ms)
{
	int	status;

	waitpid(ms->last_pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (status);
}

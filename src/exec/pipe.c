/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:41:03 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/02 19:14:01 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_pipe(t_ms *ms, int fd_pipe[2], int is_last)
{
	if (!is_last && pipe(fd_pipe) == -1)
		perror("Error at process_pipe");
	if (is_last)
		ms->fd_out = STDOUT_FILENO;
	else
	{
		ms->fd_out = fd_pipe[1];
		ms->fd_in = fd_pipe[0];
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

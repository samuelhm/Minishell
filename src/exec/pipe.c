/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:41:03 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/03 19:42:35 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

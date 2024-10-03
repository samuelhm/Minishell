/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:04:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/03 16:34:58 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_last_cmd(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (has_redirection(av + i, PIPE_S))
			return (false);
		i++;
	}
	return (true);
}

char	*getpath(t_hash *env, char *file)
{
	char	*path;
	char	**paths;
	int		i;
	char	*temp;

	path = strdup(lookup_hash(env, "PATH"));
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	free (path);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, file);
		free(temp);
		if (!access(path, F_OK | X_OK | R_OK))
		{
			free_array(paths);
			return (path);
		}
		free(path);
		path = NULL;
		i++;
	}
	free_array(paths);
	return (NULL);
}

int	process_line(t_ms *ms)
{
	int		fd_pipe[2];
	int		is_last;
	char	*path;
	int		i;

	ms->fd_in = STDIN_FILENO;
	is_last = 0;
	i = 0;
	while (ms->av[i])
	{
		if (setup_redirections(ms))
			i += 2;
		if (is_last_cmd(ms->av + i))
			is_last = 1;
		path = getpath(ms->env, ms->av[i]);
		if (!path)
		{
			fprintf(stderr, "minishell: command not found: %s\n", ms->av[0]);
			return (127);
		}
		process_pipe(ms, fd_pipe, is_last);
		execute_command(ms, path, i);
		free(path);
		i += 2;
	}
	return (wait_for_last_process(ms));
}

void	execute_command(t_ms *ms, char *path, int move)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("Error no fork at execute_comand");
	if (pid == 0)
	{
		if (ms->fd_in != STDIN_FILENO)
			dup2(ms->fd_in, STDIN_FILENO);
		if (ms->fd_out != STDOUT_FILENO)
			dup2(ms->fd_out, STDOUT_FILENO);
		if (is_builtin(ms->av[move]))
			exit (exec_builtin(ms));
		else
			execve(path, ms->av + move, ms->crude_env);
	}
	ms->last_pid = pid;
}

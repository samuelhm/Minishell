/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:04:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/04 19:31:39 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_cmd(t_ms *ms)
{
	int		i;
	int		j;
	char	**cmd;

	i = 0;
	while (ms->av[i] && strcmp(ms->av[i], PIPE_S) != 0)
		i++;
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (NULL);
	j = 0;
	while (j < i)
	{
		cmd[j] = strdup(ms->av[j]);
		j++;
	}
	cmd[j] = NULL;
	if (ms->av[i] && strcmp(ms->av[i], PIPE_S) == 0)
		i++;
	j = 0;
	while (ms->av[i])
	{
		free(ms->av[j]);
		ms->av[j] = ms->av[i];
		j++;
		i++;
	}
	ms->av[j] = NULL;
	return (cmd);
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
	int		pipi;
	char	**cmd;

	pipi = 0;
	if (!has_redirection(ms->av, PIPE_S))
		execute_simple_comand(ms);
	else
	{
		init_pipes(ms);
		cmd = get_cmd(ms);
		while (ms->fd_pipe[pipi])
		{
			if (pipi == 0)
			{
				execute_command(ms, STDIN_FILENO, ms->fd_pipe[0][1], cmd);
				close(ms->fd_pipe[0][1]);
			}
			else if (ms->fd_pipe[pipi + 1] != NULL)
			{
				execute_command(ms, ms->fd_pipe[pipi -1][0], ms->fd_pipe[pipi][1], cmd);
				close(ms->fd_pipe[pipi -1][0]);
				close(ms->fd_pipe[pipi][1]);
			}
			pipi++;
			free_array(cmd);
			cmd = get_cmd(ms);
		}
		execute_command(ms, ms->fd_pipe[pipi -1][0], STDOUT_FILENO, cmd);
		close(ms->fd_pipe[pipi -1][0]);
		free_array(cmd);
	}
	return (wait_for_last_process(ms));
}


void	execute_command(t_ms *ms, int fd_in, int fd_out, char **cmd)
{
	pid_t	pid;
	char	*path;

	path = getpath(ms->env, cmd[0]);
	pid = fork();
	if (pid == -1)
	{
		if (path)
			free(path);
		perror("Error no fork at execute_comand");
	}
	if (pid == 0)
	{
		set_child_signals();
		if (fd_in != STDIN_FILENO)
		{
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		if (fd_out != STDOUT_FILENO)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		setup_redirections(ms);
		remove_redirections(ms->av);
		if (is_builtin(cmd[0]))
			exit (exec_builtin(cmd, ms->env));
		if (!path)
			exit (EXIT_FAILURE);
		else
		{
			execve(path, cmd, ms->crude_env);
			exit(EXIT_FAILURE);
		}
	}
	if (pid != 0)
	{
		if (path)
			free(path);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
	}
	ms->last_pid = pid;
}


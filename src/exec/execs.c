/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:04:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/07 11:33:33 by shurtado         ###   ########.fr       */
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
	if (ms->av[i])
	{
		num = count_av_elements(&ms->av[i]) + 1;
		memmove(ms->av, &ms->av[i], num * sizeof(char *));
	}
	return (cmd);
}

char	*getpath(t_hash *env, char *file)
{
	char	*path;
	char	**paths;
	int		i;
	char	*temp;

	if (lookup_hash(env, "PATH") == NULL)
		path = NULL;
	else
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
		cmd = get_cmd(ms, 0, 0);
		while (ms->fd_pipe[pipi])
		{
			if (pipi == 0)
			{
				execute_command(ms, STDIN_FILENO, ms->fd_pipe[0][1], cmd);
				close(ms->fd_pipe[0][1]);
			}
			else if (ms->fd_pipe[pipi] != NULL)
			{
				execute_command(ms, ms->fd_pipe[pipi -1][0], ms->fd_pipe[pipi][1], cmd);
				close(ms->fd_pipe[pipi -1][0]);
				close(ms->fd_pipe[pipi][1]);
			}
			pipi++;
			free_array(cmd);
			cmd = get_cmd(ms, 0, 0);
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
		if (setup_redirections(cmd))
			remove_redirections(cmd);
		if (is_builtin(cmd[0]))
			exit (exec_builtin(cmd, ms->env, &ms->crude_env));
		if (!path)
		{
			execve(cmd[0], cmd, ms->crude_env);
			perror(cmd[0]);
			exit (EXIT_FAILURE);
		}
		else
		{
			execve(path, cmd, ms->crude_env);
			perror(cmd[0]);
			exit(EXIT_FAILURE);
		}
	}
	if (path)
		free(path);
	ms->last_pid = pid;
}


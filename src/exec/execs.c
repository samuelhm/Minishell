/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:04:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/04 16:04:26 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!has_redirection(ms->av, PIPE_S))
		execute_simple_comand(ms);
	return (wait_for_last_process(ms));
}

/*
void	execute_command(t_ms *ms, int fd_in, int fd_out)
{
	pid_t	pid;
	int		i;
	char	*path;
	int		j;

	i = 0;
	j = 0;
	path = getpath(ms->crude_env, args[0]);
	if (!path && !is_builtin(args[0]))
	{
		fprintf(stderr, "minishell: command not found: %s\n", args[0]);
		ms->status = 127;
		return ;
	}
	if (is_builtin(args[0]))
	{
		ms->status = exec_builtin(ms);
		if (path)
			free(path);
		return ;
	}
	pid = fork();
	if (pid == -1)
		perror("Error no fork at execute_comand");
	if (pid == 0)
	{
		if (fd_in != STDIN_FILENO)
			dup2(fd_in, STDIN_FILENO);
		if (fd_out != STDOUT_FILENO)
		{
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		if (execve(path, args, ms->crude_env) == -1)
		{
			perror("Error en execve");
			exit(1);
		}
	}
	ms->last_pid = pid;
	if (path)
		free(path);
}
*/

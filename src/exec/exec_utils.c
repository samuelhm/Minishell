/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:16:28 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/17 19:22:43 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_executable_path(char **paths, char *file)
{
	int		i;
	char	*path;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, file);
		free(temp);
		if (access(path, F_OK | X_OK | R_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*get_path_from_env(t_hash *env)
{
	char	*path;

	if (lookup_hash(env, "PATH") == NULL)
		return (NULL);
	path = strdup(lookup_hash(env, "PATH"));
	return (path);
}

char	*getpath(t_hash *env, char *file)
{
	char	**paths;
	char	*path;

	if (access(file, F_OK | X_OK | R_OK) == 0)
	{
		path = ft_strdup(file);
		return (path);
	}
	path = get_path_from_env(env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	free(path);
	path = find_executable_path(paths, file);
	free_array(paths);
	return (path);
}

static void	exe_child(t_ms *ms, int fd_in_out[2], char **cmd)
{
	char	*path;
	char	**cmdcp;

	cmdcp = cmd;
	while (!strcmp(cmdcp[0], DOUBLE_LESS) || !strcmp(cmdcp[0], LESS_S))
	{
		if (cmdcp[2])
			cmdcp += 2;
		else
			break ;
	}
	path = getpath(ms->env, cmdcp[0]);
	if (!setup_redirections(cmd))
		exit (EXIT_FAILURE);
	remove_redirections(cmd);
	set_child_signals();
	move_std(&fd_in_out);
	if (is_builtin(cmd[0]))
		exit(exec_builtin(cmd, ms->env, &ms->crude_env));
	if (!path)
		err_child(cmd);
	execve(path, cmd, ms->crude_env);
}

void	exe_cmd(t_ms *ms, int fd_in, int fd_out, char **cmd)
{
	pid_t	pid;
	int		fd_in_out[2];

	fd_in_out[0] = fd_in;
	fd_in_out[1] = fd_out;
	pid = fork();
	if (pid == -1)
		perror("Error no fork at execute_comand");
	if (pid == 0)
		exe_child(ms, fd_in_out, cmd);
	ms->last_pid = pid;
	ft_lstadd_front(&ms->pidlst, ((void *)(intptr_t)pid));
}

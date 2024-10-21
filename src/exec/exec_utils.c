/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:16:28 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/22 00:34:27 by shurtado         ###   ########.fr       */
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

static int	get_fd(int *fd, int mode)
{
	if (mode == IN)
	{
		if (fd == NULL)
			return (STDIN_FILENO);
		else
		{
			close(fd[1]);
			return (fd[0]);
		}
	}
	else if (mode == OUT)
	{
		if (fd == NULL)
			return (STDOUT_FILENO);
		else
		{
			close(fd[0]);
			return (fd[1]);
		}
	}
	else
		exit (127);
}

static void	close_all_pipes(int **plist, int *fd_in, int *fd_out)
{
	if (!plist)
		return ;
	while (*plist)
	{
		if (*plist && *plist != fd_in)
		{
			if ((*plist)[0] && !isatty((*plist)[0]))
				close((*plist)[0]);
		}
		if (*plist && *plist != fd_out)
		{
			if ((*plist)[1] && !isatty((*plist)[1]))
				close((*plist)[1]);
		}
		plist++;
	}
}

static void	exe_child(t_ms *ms, char **cmd, int *in_fd, int *out_fd)
{
	char	*path;
	int		fd_in;
	int		fd_out;

	fd_in = get_fd(in_fd, IN);
	fd_out = get_fd(out_fd, OUT);
	set_child_signals();
	if (!setup_redirections(cmd, fd_in, fd_out))
	{
		if (fd_in != -1)
			close(fd_in);
		if (fd_out != -1)
			close(fd_out);
		perror("Redirecton ERR");
		exit(EXIT_FAILURE);
	}
	close_all_pipes(ms->fd_pipe, in_fd, out_fd);
	remove_redirections(cmd);
	path = getpath(ms->env, cmd[0]);
	if (is_builtin(cmd[0]))
		exit(exec_builtin(cmd, ms->env, &ms->crude_env));
	if (!path)
		err_child(cmd);
	execve(path, cmd, ms->crude_env);
}

void	exe_cmd(t_ms *ms, int *fd_in, int *fd_out, char **cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("Error no fork at execute_comand");
	if (pid == 0)
		exe_child(ms, cmd, fd_in, fd_out);
	ms->last_pid = pid;
	ft_lstadd_back(&ms->pidlst, ft_lstnew((void *)(intptr_t)pid));
}

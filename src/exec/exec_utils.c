/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:16:28 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/18 02:25:41 by shurtado         ###   ########.fr       */
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

static void	dup_close_child(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
		{
			perror("Error duplicando fd_in a STDIN");
			exit(EXIT_FAILURE);
		}
		close(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
		{
			perror("Error duplicando fd_out a STDOUT");
			exit(EXIT_FAILURE);
		}
		close(fd_out);
	}
}

static void	exe_child(t_ms *ms, char **cmd, int fd_in, int fd_out)
{
	char	*path;

	dup_close_child(fd_in, fd_out);
	path = getpath(ms->env, cmd[0]);
	set_child_signals();
	if (is_builtin(cmd[0]))
		exit(exec_builtin(cmd, ms->env, &ms->crude_env));
	if (!path)
		err_child(cmd);
	execve(path, cmd, ms->crude_env);
}

void	exe_cmd(t_ms *ms, int fd_in, int fd_out, char **cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("Error no fork at execute_comand");
	if (pid == 0)
	{
		exe_child(ms, cmd, fd_in, fd_out);
	}
	ms->last_pid = pid;
	ft_lstadd_front(&ms->pidlst, ft_lstnew((void *)(intptr_t)pid));
}

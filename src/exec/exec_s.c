/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:40:42 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/14 21:20:57 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_process(t_ms *ms, char *path)
{
	set_child_signals();
	if (!setup_redirections(ms->av))
	{
		perror("Errores en la redirección!");
		exit(EXIT_FAILURE);
	}
	remove_redirections(ms->av);
	if (!path || !strcmp(path, "/"))
	{
		if (ms->av[0])
			ft_printf("%s: no se encontró la orden\n", ms->av[0]);
		exit(127);
	}
	execve(path, ms->av, ms->crude_env);
	perror("File not exist or");
	exit(EXIT_FAILURE);
}

static void	handle_parent_process(t_ms *ms, char *path, pid_t pid)
{
	if (pid == -1)
	{
		if (path)
			free(path);
		perror("Error no fork at execute_comand");
	}
	if (path)
		free(path);
	ms->last_pid = pid;
}

static void	restore_fd_redir(int (*save)[])
{
	dup2((*save)[0], STDOUT_FILENO);
	dup2((*save)[1], STDIN_FILENO);
	close((*save)[0]);
	close((*save)[1]);
}

void	execute_simple_comand(t_ms *ms)
{
	pid_t	pid;
	char	*path;
	int		save[2];
	char	**avpath;

	avpath = ms->av;
	if (has_builtin(ms->av))
	{
		save[0] = dup(STDOUT_FILENO);
		save[1] = dup(STDIN_FILENO);
		setup_redirections(ms->av);
		remove_redirections(ms->av);
		ms->status = exec_builtin(ms->av, ms->env, &ms->crude_env);
		restore_fd_redir(&save);
		return ;
	}
	init_signals(CHILD);
	while (!strcmp(avpath[0], DOUBLE_LESS))
		if (avpath[2])
			avpath += 2;
		else
			break ;
	if (avpath[0])
		path = getpath(ms->env, avpath[0]);
	pid = fork();
	if (pid == 0)
		handle_child_process(ms, path);
	handle_parent_process(ms, path, pid);
}

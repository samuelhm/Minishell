/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:09:31 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/04 21:12:08 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env") || \
			!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "exit") || \
			!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "pwd") || \
			!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "debug"))
	{
		return (true);
	}
	return (false);
}

int	exec_builtin(char **cmd, t_hash *env)
{
	char	*blt;

	blt = cmd[0];
	if (!strcmp(blt, "echo"))
		return (blt_echo(cmd));
	else if (!strcmp(blt, "env"))
		return (blt_env(env));
	else if (!strcmp(blt, "cd"))
		return (blt_cd(cmd, env));
	else if (!strcmp(blt, "export"))
		return (blt_export(cmd, env));
	else if (!strcmp(blt, "pwd"))
		return (blt_pwd());
	else if (!strcmp(blt, "unset"))
		return (blt_unset(cmd, env));
	else
		return (-1);
	return (0);
}

void	execute_simple_comand(t_ms *ms)
{
	pid_t	pid;
	char	*path;

	path = getpath(ms->env, ms->av[0]);
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
		if (!setup_redirections(ms->av))
		{
			perror("Errores en la redirección!");
			exit(EXIT_FAILURE);
		}
		remove_redirections(ms->av);
		if (is_builtin(ms->av[0]))
			exit (exec_builtin(ms->av, ms->env));
		if (!path)
			exit (EXIT_FAILURE);
		else
		{
			execve(path, ms->av, ms->crude_env);
			perror("EXECVE FAIL");
			if (path)
				free(path);
			exit(EXIT_FAILURE);
		}
	}
	if (path)
		free(path);
	ms->last_pid = pid;
}

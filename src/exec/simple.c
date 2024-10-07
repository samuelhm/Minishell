/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:09:31 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/07 14:07:17 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	has_builtin(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (is_builtin(cmd[i]))
			return (true);
		i++;
	}
	return (false);
}

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

int	exec_builtin(char **cmd, t_hash *env, char ***crude)
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
		return (blt_export(cmd, env, crude));
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
	int		save;

	if (has_builtin(ms->av))
	{
		save = dup(STDOUT_FILENO);
		setup_redirections(ms->av);
		remove_redirections(ms->av);
		ms->status = exec_builtin(ms->av, ms->env, &ms->crude_env);
		dup2(save, STDOUT_FILENO);
		close(save);
		return ;
	}
	init_signals(CHILD);
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
		if (!path)
		{
			exit (execve(ms->av[0], ms->av, ms->crude_env));
			perror(ms->av[0]);
		}
		else
			exit (execve(path, ms->av, ms->crude_env));
	}
	if (path)
		free(path);
	ms->last_pid = pid;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:09:31 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/30 16:15:31 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	execute_command(char *path, char **args, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(path, args, env) == -1)
		{
			perror("execve");
			return (1);
		}
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		perror("fork");
		return (1);
	}
	return (0);
}

bool	is_builtin(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!ft_strcmp(av[i], "echo") || !ft_strcmp(av[i], "env") || \
				!ft_strcmp(av[i], "cd") || !ft_strcmp(av[i], "exit") || \
				!ft_strcmp(av[i], "export") || !ft_strcmp(av[i], "pwd") || \
				!ft_strcmp(av[i], "unset") || !ft_strcmp(av[i], "debug"))
		{
			return (true);
		}
		i++;
	}
	return (false);
}

int	exec_builtin(t_ms *ms)
{
	char	*blt;

	blt = ms->av[0];
	if (!strcmp(blt, "echo"))
		blt_echo(ms->av);
	else if (!strcmp(blt, "env"))
		blt_env(ms->env);
	else if (!strcmp(blt, "cd"))
		blt_cd(ms->av, ms->env);
	else if (!strcmp(blt, "exit"))
		blt_exit(ms);
	else if (!strcmp(blt, "export"))
		blt_export(ms->av, ms->env);
	else if (!strcmp(blt, "pwd"))
		blt_pwd();
	else if (!strcmp(blt, "unset"))
		blt_unset(ms->av, ms->env);
	else if (!strcmp(blt, "debug"))
		show_debug(ms);
	else
		return (1);
	return (0);
}

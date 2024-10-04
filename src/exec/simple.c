/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:09:31 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/04 15:58:06 by shurtado         ###   ########.fr       */
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

int	exec_builtin(t_ms *ms)
{
	char	*blt;

	blt = ms->av[0];
	if (!strcmp(blt, "echo"))
		return (blt_echo(ms->av));
	else if (!strcmp(blt, "env"))
		return (blt_env(ms->env));
	else if (!strcmp(blt, "cd"))
		return (blt_cd(ms->av, ms->env));
	else if (!strcmp(blt, "exit"))
		return (blt_exit(ms));
	else if (!strcmp(blt, "export"))
		return (blt_export(ms->av, ms->env));
	else if (!strcmp(blt, "pwd"))
		return (blt_pwd());
	else if (!strcmp(blt, "unset"))
		return (blt_unset(ms->av, ms->env));
	else if (!strcmp(blt, "debug"))
		show_debug(ms);
	else
		return (-1);
	return (0);
}

void	execute_simple_comand(t_ms *ms)
{
	pid_t	pid;
	char	*path;
	int		return_status;

	pid = fork();
	if (pid == -1)
		perror("Error no fork at execute_comand");
	if (pid == 0)
	{
		if (!setup_redirections(ms))
		{
			perror("Errores en la redirección!");
			exit(EXIT_FAILURE);
		}
		remove_redirections(ms->av);
		if (is_builtin(ms->av[0]))
		{
			exit (exec_builtin(ms));
		}
		path = getpath(ms->env, ms->av[0]);
		if (!path)
			exit (EXIT_FAILURE);
		else
		{
			return_status = execve(path, ms->av, get_env_arr(ms));
			free(path);
			exit(return_status);
		}
	}
	ms->last_pid = pid;
}

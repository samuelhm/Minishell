/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:09:31 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/20 16:55:57 by shurtado         ###   ########.fr       */
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
	if (!cmd || !cmd[0])
		return (false);
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
	else if (!strcmp(blt, "exit"))
		return (blt_exit(cmd));
	else
		return (-1);
	return (0);
}

int	all_digits(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!isdigit((unsigned char)str[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_exit_args(t_ms *ms)
{
	if (ms->av[1])
	{
		if (ms->av[2])
		{
			ft_printf("exit: too many arguments\n");
			free_array(ms->av);
			return (1);
		}
		if (!all_digits(ms->av[1]))
		{
			ft_printf(EXITERR, ms->av[1]);
			free_resources(ms);
			exit (2);
		}
		ms->status = ft_atoi(ms->av[1]);
	}
	free_resources(ms);
	exit(ms->status);
	return (0);
}

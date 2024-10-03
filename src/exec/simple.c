/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:09:31 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/02 19:13:11 by shurtado         ###   ########.fr       */
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

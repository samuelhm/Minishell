/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:58:35 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/19 02:00:13 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shift_av_entries(t_ms *ms, int start)
{
	int		num;

	num = 0;
	while (ms->av[start])
		ms->av[num++] = ms->av[start++];
	while (ms->av[num])
	{
		free(ms->av[num]);
		ms->av[num++] = NULL;
	}
}

void	free_av_entries(t_ms *ms, int limit)
{
	int	num;

	num = 0;
	while (num < limit)
	{
		free(ms->av[num]);
		ms->av[num] = NULL;
		num++;
	}
}

void	copy_arguments(char **av, char **cmd, int i_end)
{
	int	j;

	j = 0;
	while (j < i_end)
	{
		cmd[j] = strdup(av[j]);
		j++;
	}
	cmd[j] = NULL;
}

char	**get_cmd(char **av)
{
	int		i_end;
	char	**cmd;

	i_end = find_pipe_position(av);
	cmd = allocate_command_array(i_end);
	if (!cmd)
		return (NULL);
	copy_arguments(av, cmd, i_end);
	return (cmd);
}

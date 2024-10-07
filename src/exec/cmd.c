/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:58:35 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/07 20:17:08 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shift_av_entries(t_ms *ms, int start)
{
	int	num;

	num = 0;
	while (ms->av[start])
	{
		ms->av[num++] = ms->av[start++];
	}
	ms->av[num] = NULL;
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

void	update_av_after_pipe(t_ms *ms, int i_end)
{
	if (ms->av[i_end] && strcmp(ms->av[i_end], PIPE_S) == 0)
		i_end++;
	free_av_entries(ms, i_end);
	shift_av_entries(ms, i_end);
}

void	copy_arguments(t_ms *ms, char **cmd, int i_end)
{
	int	j;

	j = 0;
	while (j < i_end)
	{
		cmd[j] = strdup(ms->av[j]);
		j++;
	}
	cmd[j] = NULL;
}

char	**get_cmd(t_ms *ms)
{
	int		i_end;
	char	**cmd;

	i_end = find_pipe_position(ms->av);
	cmd = allocate_command_array(i_end);
	if (!cmd)
		return (NULL);
	copy_arguments(ms, cmd, i_end);
	update_av_after_pipe(ms, i_end);
	return (cmd);
}

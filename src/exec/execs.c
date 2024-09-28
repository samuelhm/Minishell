/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:04:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/28 12:56:12 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_line(t_ms *ms)
{
	char	*path;

	path = ft_strjoin("/bin/", ms->av[0]);
	if (!path)
		return (1);
	if (has_any_redirect(ms->av))
		do_redirection(ms->av);
	if (is_builtin(ms->av))
		exec_builtin(ms);
	else
		execute_command(path, ms->av, get_env_arr(ms));
	free(path);
	return (0);
}


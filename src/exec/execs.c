/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:04:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/27 10:38:23 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_line(t_ms *ms)
{
	if (has_any_redirect(ms->av))
		do_redirection(ms->av);
	if (has_pipe(ms->av))
		return (0);
	if (is_builtin(ms->av))
		exec_builtin(ms);
	else
		execute_command(ms->av, ms->raw_env);
	return (0);
}


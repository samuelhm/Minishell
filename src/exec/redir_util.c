/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:50:34 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/03 16:12:48 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_input_redirection(t_ms *ms)
{
	char	*filename;

	if (has_redirection(ms->av, "<"))
	{
		filename = get_filename(ms->av, "<");
		ms->fd_in = open(filename, O_RDONLY);
		free(filename);
		return (true);
	}
	return (false);
}

bool	handle_output_trunc_redirection(t_ms *ms)
{
	char	*filename;

	if (has_redirection(ms->av, ">"))
	{
		filename = get_filename(ms->av, ">");
		ms->fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		free(filename);
		return (true);
	}
	return (false);
}

bool	handle_output_append_redirection(t_ms *ms)
{
	char	*filename;

	if (has_redirection(ms->av, ">>"))
	{
		filename = get_filename(ms->av, ">>");
		ms->fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		free(filename);
		return (true);
	}
	return (false);
}

bool	handle_heredoc_redirection(t_ms *ms)
{
	char	*filename;

	if (has_redirection(ms->av, "<<"))
	{
		filename = get_filename(ms->av, "<<");
		ms->fd_in = handle_heredoc(filename);
		free(filename);
		return (true);
	}
	return (false);
}

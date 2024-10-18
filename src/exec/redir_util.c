/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:50:34 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/18 01:53:58 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_heredoc_redirection(char **av)
{
	int		fd_in;
	char	*filename;
	char	**av2;

	av2 = av;

	while (has_redirection(av2, "<<"))
	{
		filename = get_filename(av2, "<<");
		fd_in = handle_heredoc(filename);
		free(filename);
		if (fd_in == -1)
		{
			return (false);
		}
		if (!has_redirection(av2 + 2, "<<"))
			dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		av2 += 2;
	}
	return (true);
}

bool	handle_input_redirection(char **av)
{
	int		fd_in;
	char	*filename;
	char	**av2;

	av2 = av;
	while (has_redirection(av2, "<"))
	{
		filename = get_filename(av2, "<");
		fd_in = open(filename, O_RDONLY);
		if (fd_in == -1)
		{
			exit_error_redir(&filename);
			return (false);
		}
		free(filename);
		if (!has_redirection(av2 + 2, "<"))
			dup2(fd_in, STDIN_FILENO);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		av2 += 2;
	}
	return (true);
}

static char	*get_next_output(char **av)
{
	while (av)
	{
		if (!strcmp(av[0], MORE_S) || !strcmp(av[0], DOUBLE_MORE))
			return (av[0]);
		av++;
	}
	return (NULL);
}

bool	handle_single_redirection(char ***av, char *next, int *fd_out)
{
	char	*filename;

	filename = get_filename(*av, next);
	if (!strcmp(next, ">"))
		*fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!strcmp(next, ">>"))
		*fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		*fd_out = -1;
	if (*fd_out == -1)
	{
		write(2, "No se puede crear o modificar: ", 31);
		write(2, filename, ft_strlen(filename));
		write(2, "\n", 1);
		free(filename);
		return (false);
	}
	free(filename);
	if (!has_redirection(*av + 2, MORE_S) && \
		!has_redirection(*av + 2, DOUBLE_MORE))
		dup2(*fd_out, STDOUT_FILENO);
	return (true);
}

bool	handle_output_redirection(char **avo)
{
	int		fd_out;
	char	*next;
	char	**av;

	av = avo;
	while (has_redirection(av, MORE_S) || has_redirection(av, DOUBLE_MORE))
	{
		next = get_next_output(av);
		while (strcmp(av[0], next))
			av++;
		if (!handle_single_redirection(&av, next, &fd_out))
			return (false);
		close(fd_out);
		av++;
	}
	return (true);
}

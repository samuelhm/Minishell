/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:50:34 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/15 15:43:28 by shurtado         ###   ########.fr       */
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
			return (false);
		if (!has_redirection(av2 + 2, "<<"))
			dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		av2 += 2;
	}
	if (has_redirection(av, "<<"))
		return (true);
	return (false);
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
			write(2, filename, strlen(filename));
			free(filename);
			write(2, ": no such file or directory\n", 29);
			exit(1);
			return (false);
		}
		free(filename);
		if (!has_redirection(av2 + 2, "<"))
			dup2(fd_in, STDIN_FILENO);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		av2 += 2;
	}
	if (has_redirection(av, "<"))
		return (true);
	return (false);
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

bool	handle_output_redirection(char **av)
{
	int		fd_out;
	char	*filename;
	char	*next;

	while (has_redirection(av, MORE_S) || has_redirection(av, DOUBLE_MORE))
	{
		next = get_next_output(av);
		filename = get_filename(av, next);
		if (!strcmp(next, ">"))
			fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (!strcmp(next, ">>"))
			fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd_out = -1;
		free(filename);
		if (fd_out == -1)
		{
			write(2, "No se puede crear o modificar: ", 31);
			write(2, filename, ft_strlen(filename));
			write(2, "\n", 1);
			exit(1);
		}
		if (!has_redirection(av + 2, MORE_S) && \
			!has_redirection(av + 2, DOUBLE_MORE))
			dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		av++;
	}
	if (has_redirection(av + 2, MORE_S) || \
		has_redirection(av + 2, DOUBLE_MORE))
		return (true);
	return (false);
}

void	remove_redirections(char **av)
{
	int		i;
	int		j;

	i = 0;
	while (av[i] && ft_strcmp(av[i], PIPE_S) != 0)
	{
		if (is_special(av[i]))
		{
			j = i;
			free(av[i]);
			free(av[i + 1]);
			while (av[j + 2])
			{
				av[j] = av[j + 2];
				j++;
			}
			av[j] = NULL;
			av[j + 1] = NULL;
		}
		else
			i++;
	}
}

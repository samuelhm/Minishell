/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:50:34 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/14 20:58:29 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_input_redirection(char **av)
{
	int		fd_in;
	char	*filename;

	if (has_redirection(av, "<"))
	{
		filename = get_filename(av, "<");
		fd_in = open(filename, O_RDONLY);
		free(filename);
		if (fd_in == -1)
			return (false);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		return (true);
	}
	return (true);
}

bool	handle_output_trunc_redirection(char **av)
{
	int		fd_out;
	char	*filename;

	if (has_redirection(av, ">"))
	{
		filename = get_filename(av, ">");
		fd_out = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		free(filename);
		if (fd_out == -1)
			return (false);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		return (true);
	}
	return (true);
}

bool	handle_output_append_redirection(char **av)
{
	int		fd_out;
	char	*filename;

	if (has_redirection(av, ">>"))
	{
		filename = get_filename(av, ">>");
		fd_out = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		free(filename);
		if (fd_out == -1)
			return (false);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
		return (true);
	}
	return (false);
}

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
		if (!has_redirection(av2 +2, "<<"))
			dup2(fd_in, STDIN_FILENO);
		close(fd_in);
		av2 += 2;
	}
	if (has_redirection(av, "<<"))
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

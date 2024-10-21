/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:50:34 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/22 00:36:03 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prepare_std_in(char **av, int fd_in)
{
	if (has_redirection(av, LESS_S) && fd_in != -1 && fd_in != STDIN_FILENO)
		close(fd_in);
	else if (fd_in != -1 && !isatty(fd_in) && fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
}

bool	handle_input_redirection(char **av, int fd_in)
{
	int		file;

	prepare_std_in(av, fd_in);
	while (*av)
	{
		if (!ft_strcmp(*av, LESS_S) && av[1])
		{
			file = open(av[1], O_RDONLY);
			if (file == -1)
				return (false);
			if (file != STDIN_FILENO)
			{
				dup2(file, STDIN_FILENO);
				close(file);
			}
			av++;
		}
		av++;
	}
	return (true);
}

void	prepare_std_out(char **av, int fd_out)
{
	if ((has_redirection(av, MORE_S) || has_redirection(av, DOUBLE_MORE)) \
		&& fd_out != -1 && fd_out != STDOUT_FILENO)
		close(fd_out);
	else if (fd_out != -1 && !isatty(fd_out) && fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

bool	handle_output_redirection(char **av, int fd_out)
{
	int		file;

	prepare_std_out(av, fd_out);
	while (*av)
	{
		if ((!strcmp(*av, MORE_S) || !strcmp(*av, DOUBLE_MORE)) && av[1])
		{
			if (!strcmp(*av, MORE_S))
				file = open(av[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				file = open(av[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (file < 0)
				return (false);
			if (file != STDOUT_FILENO)
			{
				dup2(file, STDOUT_FILENO);
				close(file);
			}
			av++;
		}
		av++;
	}
	return (true);
}

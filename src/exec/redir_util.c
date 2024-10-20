/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:50:34 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/20 14:17:01 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	catch_heredocs(char **av, int fd_in)
{
	static int	i;
	char		*filename;
	int			file;

	if(has_redirection(av, DOUBLE_LESS) && fd_in != -1  && fd_in != STDIN_FILENO)
		close(fd_in);
	else if (fd_in != -1 && !isatty(fd_in))
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	i++;
	filename = ft_strdup("/tmp/tmpa");
	filename[8] += i;
	while (*av)
	{
		if (!ft_strcmp(*av, DOUBLE_LESS) && av[1])
		{
			file = open(filename,O_RDONLY);
			i++;
			filename[3] += i;
			if (file == -1)
			{
				free(filename);
				perror("error, lecura de heredoc");
				return (false);
			}
			if (file != STDIN_FILENO)
			{
				dup2(file, STDIN_FILENO);
				close(file);
			}
			av++;
		}
		av++;
	}
	free(filename);
	return (true);
}

bool	handle_input_redirection(char **av, int fd_in)
{
	int		file;

	if (has_redirection(av, LESS_S) && fd_in != -1 && fd_in != STDIN_FILENO)
		close(fd_in);
	else if (fd_in != -1 && !isatty(fd_in) && fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	while (*av)
	{
		if (!ft_strcmp(*av, LESS_S) && av[1])
		{
			file = open(av[1], O_RDONLY);
			if (file == -1)
			{
				perror(av[1]);
				return (false);
			}
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

bool	handle_output_redirection(char **av, int fd_out)
{
	int		file;

	if ((has_redirection(av, MORE_S) || has_redirection(av, DOUBLE_MORE)) \
		&& fd_out != -1 && fd_out != STDOUT_FILENO)
		close(fd_out);
	else if (fd_out != -1 && !isatty(fd_out) && fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	while (*av)
	{
		if ((!strcmp(*av, MORE_S) || !strcmp(*av, DOUBLE_MORE)) && av[1])
		{
			if (!strcmp(*av, MORE_S))
				file = open(av[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				file = open(av[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (file < 0)
			{
				perror("Error al crear el archivo.");
				return (false);
			}
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

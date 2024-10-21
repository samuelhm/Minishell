/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctch_hdoc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 00:35:33 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/22 00:44:48 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prepare_hdoc_catch(char **av, int fd_in)
{
	if (has_redirection(av, DOUBLE_LESS) && \
		fd_in != -1 && fd_in != STDIN_FILENO)
		close(fd_in);
	else if (fd_in != -1 && !isatty(fd_in))
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
}

static bool	check_file(char *filename)
{
	int			file;

	file = open(filename, O_RDONLY);
	if (file == -1)
	{
		free(filename);
		perror("Error de heredoc");
		return (false);
	}
	if (file != STDIN_FILENO)
	{
		dup2(file, STDIN_FILENO);
		close(file);
	}
	unlink(filename);
	return (true);
}

bool	catch_heredocs(char **av, int fd_in)
{
	char		*filename;

	prepare_hdoc_catch(av, fd_in);
	filename = ft_strdup("/tmp/tmpa");
	while (*av)
	{
		if (!ft_strcmp(*av, DOUBLE_LESS) && av[1])
		{
			while (access(filename, R_OK) != 0 && filename[8] < 'z')
				filename[8]++;
			if (filename[8] > 'z')
				return (false);
			if (!check_file(filename))
				return (false);
			av++;
		}
		av++;
	}
	free(filename);
	return (true);
}

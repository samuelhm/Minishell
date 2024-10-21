/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:07:00 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/21 20:52:35 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERRFILE "minishell: syntax error near unexpected token `%s`\n"

bool	has_redirection(char **av, char *redir)
{
	int	i;

	i = 0;
	if (!av || !av[0])
		return (false);
	while (av[i])
	{
		if (!strcmp(av[i], redir))
			return (true);
		i++;
	}
	return (false);
}

bool	setup_redirections(char **cmd, int fd_in, int fd_out)
{
	if (!catch_heredocs(cmd, fd_in))
		return (false);
	if (!handle_input_redirection(cmd, fd_in))
		return (false);
	if (!handle_output_redirection(cmd, fd_out))
		return (false);
	return (true);
}

static void	heredoc_loop(int tempfile, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, tempfile);
		ft_putstr_fd("\n", tempfile);
		free(line);
	}
}

bool	handle_heredoc(char *delimiter)
{
	char		*filename;
	int			tempfile;
	static int	i;

	i++;
	filename = ft_strdup("/tmp/tmpa");
	filename[8] += i;
	tempfile = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tempfile == -1)
		perror("no se puede crear tmp:");
	if (tempfile < 0)
	{
		free(filename);
		return (false);
	}
	heredoc_loop(tempfile, delimiter);
	close(tempfile);
	free(filename);
	return (true);
}

bool	make_hdoc_files(char **av)
{
	while (*av)
	{
		if (!ft_strcmp(*av, DOUBLE_LESS) && av[1])
		{
			if (!handle_heredoc(av[1]))
				return (false);
		}
		av++;
	}
	return (true);
}

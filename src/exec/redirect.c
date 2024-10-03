/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:07:00 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/03 16:52:31 by shurtado         ###   ########.fr       */
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

bool	setup_redirections(t_ms *ms)
{
	int	result;

	ms->fd_in = STDIN_FILENO;
	ms->fd_out = STDOUT_FILENO;
	result = 0;
	result += handle_input_redirection(ms);
	result += handle_output_trunc_redirection(ms);
	result += handle_output_append_redirection(ms);
	result += handle_heredoc_redirection(ms);

	if (ms->fd_in == -1 || ms->fd_out == -1)
		perror("Error en setup_redirections");
	return (result);
}

char	*get_filename(char **av, char *redir)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!strcmp(av[i], redir))
		{
			if (av[i + 1])
				return (strdup(av[i + 1]));
			else
			{
				fprintf(stderr, ERRFILE, redir);
				return (NULL);
			}
		}
		i++;
	}
	return (NULL);
}

int	handle_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
		perror("pipe error on handle_heredoc");
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
		ft_putstr_fd(line, pipe_fd[1]);
		ft_putstr_fd("\n", pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

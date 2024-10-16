/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:07:00 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/16 11:48:09 by shurtado         ###   ########.fr       */
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

bool	setup_redirections(char **cmd)
{
	if (!handle_input_redirection(cmd))
		return (false);
	if (!handle_input_redirection(cmd))
		return (false);
	if (!handle_heredoc_redirection(cmd))
		return (false);
	if (!handle_output_redirection(cmd))
		return (false);
	return (true);
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
				return (ft_strdup(av[i + 1]));
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
	{
		perror("pipe error on handle_heredoc");
		return (-1);
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:04:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/03 17:38:08 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_cmd_args(char **av)
{
	int i = 0;
	int j;

	// Eliminar el comando y sus argumentos (hasta un pipe o el final del array)
	while (av[i] && strcmp(av[i], "|"))  // Hasta encontrar un pipe
	{
		free(av[i]);  // Liberar el comando o argumento
		i++;
	}

	// Si hay un pipe en la posición av[i], lo dejamos (se parará el bucle antes del pipe)
	if (av[i] && !strcmp(av[i], "|"))
	{
		free(av[i]);  // Liberar el pipe si lo encontramos
		i++;
	}

	// Mover los elementos restantes para eliminar los vacíos
	j = 0;
	while (av[i])  // Mover los elementos restantes a la izquierda
	{
		av[j] = av[i];
		j++;
		i++;
	}
	av[j] = NULL;  // Marcar el final del array
}
void	remove_redirections(char **av)
{
	int		i;
	int		j;

	i = 0;
	while (av[i] && strcmp(av[i], PIPE_S))
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

bool	is_last_cmd(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (has_redirection(av + i, PIPE_S) || \
			has_redirection(av + i, DOUBLE_MORE) || \
			has_redirection(av + i, MORE_S))
			return (false);
		i++;
	}
	return (true);
}

char	*getpath(t_hash *env, char *file)
{
	char	*path;
	char	**paths;
	int		i;
	char	*temp;

	path = strdup(lookup_hash(env, "PATH"));
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	free (path);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, file);
		free(temp);
		if (!access(path, F_OK | X_OK | R_OK))
		{
			free_array(paths);
			return (path);
		}
		free(path);
		path = NULL;
		i++;
	}
	free_array(paths);
	return (NULL);
}

int	process_line(t_ms *ms)
{
	int		fd_pipe[2];
	int		is_last;
	char	*path;

	ms->fd_in = STDIN_FILENO;
	is_last = 0;
	while (ms->av && ms->av[0])
	{
		if (is_last_cmd(ms->av))
			is_last = 1;
		if (setup_redirections(ms))
			remove_redirections(ms->av);
		path = getpath(ms->env, ms->av[0]);
		if (!path)
		{
			fprintf(stderr, "minishell: command not found: %s\n", ms->av[0]);
			return (127);
		}
		if (has_redirection(ms->av, PIPE_S))
			process_pipe(ms, fd_pipe, is_last);
		execute_command(ms, path, 0);
		free(path);
		remove_cmd_args(ms->av);
	}
	return (wait_for_last_process(ms));
}

void	execute_command(t_ms *ms, char *path, int move)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror("Error no fork at execute_comand");
	if (pid == 0)
	{
		if (ms->fd_in != STDIN_FILENO)
			dup2(ms->fd_in, STDIN_FILENO);
		if (ms->fd_out != STDOUT_FILENO)
			dup2(ms->fd_out, STDOUT_FILENO);
		if (is_builtin(ms->av[move]))
			exit (exec_builtin(ms));
		else
			execve(path, ms->av + move, ms->crude_env);
	}
	ms->last_pid = pid;
}

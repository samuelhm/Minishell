/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:04:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/02 14:09:40 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getpath(t_hash *env, char *file)
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
	char	*path;

	path = getpath(ms->env, ms->av[0]);
	if (!path && !is_builtin(ms->av))
	{
		fprintf(stderr, "minishell: command not found: %s\n", ms->av[0]);
		return (127);
	}
	if (has_any_redirect(ms->av))
		do_redirection(ms->av);
	if (is_builtin(ms->av))
		exec_builtin(ms);
	else
	{
		execute_command(path, ms->av, ms->crude_env);
	}
	free(path);
	return (0);
}

/*
int process_line(t_ms *ms)
{
	int		i;
	int		last_pid;
	int		status;
	int		fd_pipe[2];
	int		fd_in;
	int		fd_out;
	char	*path;

	i = 0;
	fd_in = STDIN_FILENO;  // Entrada inicial, por defecto stdin
	status = 0;            // Código de salida del último proceso

	while (ms->av[i])
	{
		// Si no es el último comando, crea un pipe
		if (ms->av[i + 1] && pipe(fd_pipe) == -1)
			handle_error();

		// Comprobar si hay redirección de entrada o salida en este comando
		if (has_redirection(ms->av[i], "<"))
			fd_in = open(get_filename(ms->av[i], "<"), O_RDONLY);
		if (has_redirection(ms->av[i], "<<"))
			fd_in = handle_heredoc(get_delimiter(ms->av[i], "<<"));
		if (has_redirection(ms->av[i], ">"))
			fd_out = open(get_filename(ms->av[i], ">"), O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (has_redirection(ms->av[i], ">>"))
			fd_out = open(get_filename(ms->av[i], ">>"), O_WRONLY | O_CREAT | O_APPEND, 0644);

		path = getpath(ms->env, ms->av[i][0]);
		if (!path)
		{
			fprintf(stderr, "minishell: command not found: %s\n", ms->av[i][0]);
			return (127);  // Código estándar para "comando no encontrado"
		}

		last_pid = fork();
		if (last_pid == -1)
			handle_error();

		if (last_pid == 0)
		{
			// Proceso hijo

			// Redirección de entrada
			if (fd_in != STDIN_FILENO)
				dup2(fd_in, STDIN_FILENO);

			// Redirección de salida si no es el último comando
			if (ms->av[i + 1])
				dup2(fd_pipe[1], STDOUT_FILENO);
			else if (fd_out != STDOUT_FILENO)
				dup2(fd_out, STDOUT_FILENO);  // Redirección de salida a archivo

			// Cerrar los descriptores de pipe
			close(fd_pipe[0]);
			close(fd_pipe[1]);

			// Ejecuta el comando
			execve(path, ms->av[i], ms->env);
			handle_error();  // Solo se ejecuta si execve falla
		}
		else
		{
			// Proceso padre

			// Cerrar la escritura del pipe y actualizar fd_in para el próximo comando
			close(fd_pipe[1]);
			if (fd_in != STDIN_FILENO)
				close(fd_in);
			fd_in = fd_pipe[0];  // La salida del pipe anterior será la entrada del siguiente comando

			// Liberar memoria del path
			free(path);

			// Avanza al siguiente comando
			i++;
		}
	}

	// Espera al último proceso hijo y obtiene su código de salida
	waitpid(last_pid, &status, 0);

	// Retorna el código de salida del último comando
	if (WIFEXITED(status))
		return WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		return WTERMSIG(status) + 128;  // Estándar para señales
	return status;
}
*/

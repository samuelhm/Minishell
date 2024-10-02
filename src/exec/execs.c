/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:04:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/02 11:37:37 by shurtado         ###   ########.fr       */
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
		execute_command(path, ms->av, get_env_arr(ms));
	}
	free(path);
	return (0);
}


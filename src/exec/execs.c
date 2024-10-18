/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:04:36 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/18 02:19:33 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_av_elements(char **av)
{
	int	count;

	count = 0;
	while (av[count])
		count++;
	return (count);
}

int	find_pipe_position(char **av)
{
	int	i;

	i = 0;
	while (av[i] && strcmp(av[i], PIPE_S) != 0)
		i++;
	return (i);
}

char	**allocate_command_array(int size)
{
	char	**cmd;

	cmd = malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (NULL);
	return (cmd);
}

char	*get_path_from_env(t_hash *env)
{
	char	*path;

	if (lookup_hash(env, "PATH") == NULL)
		return (NULL);
	path = strdup(lookup_hash(env, "PATH"));
	return (path);
}

char	*getpath(t_hash *env, char *file)
{
	char	**paths;
	char	*path;

	if (access(file, F_OK | X_OK | R_OK) == 0)
	{
		path = ft_strdup(file);
		return (path);
	}
	path = get_path_from_env(env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	free(path);
	path = find_executable_path(paths, file);
	free_array(paths);
	return (path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:09:45 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/06 15:47:43 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*resolve_cd_path(char **av, t_hash *env)
{
	char	*path;

	if (!av[1])
	{
		path = lookup_hash(env, "HOME");
		if (!path)
		{
			ft_printf("cd: HOME not set\n");
			return (NULL);
		}
	}
	else
		path = av[1];
	return (path);
}

int	blt_cd(char **av, t_hash *env)
{
	char	*path;
	int		result;
	char	buf[PATH_MAX];
	char	*tmp;

	result = 0;
	path = resolve_cd_path(av, env);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		perror("cd");
		result = 1;
	}
	if (!result)
	{
		tmp = lookup_hash(env, "PWD");
		getcwd(buf, sizeof(buf));
		assign_hash(env, "OLDPWD", tmp);
		assign_hash(env, "PWD", buf);
	}
	if (!av[1])
		free(path);
	return (result);
}

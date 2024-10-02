/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:09:45 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/02 11:18:52 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	blt_cd(char **av, t_hash *env)
{
	char	*path;
	int		result;
	char	buf[PATH_MAX];

	result = 0;
	if (!av[1])
	{
		path = lookup_hash(env, "HOME");
		if (!path)
		{
			ft_printf("cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = av[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		result = 1;
	}
	if (!result)
	{
		getcwd(buf, sizeof(buf));
		assign_hash(env, "OLDPWD", lookup_hash(env, "PWD"));
		assign_hash(env, "PWD", buf);
	}
	if (!av[1])
		free(path);
	return (result);
}

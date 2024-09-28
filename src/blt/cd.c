/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:09:45 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/28 13:16:21 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	blt_cd(char **av, t_hash *env)
{
	char	*path;
	int		result;
\
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
	{
		path = av[1];
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		result = 1;
	}
	free(path);
	return (result);
}

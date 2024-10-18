/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:47:06 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/17 22:55:58 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_newav(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

int	count_new_size(char **av)
{
	int	i;
	int	new_size;

	i = 0;
	new_size = 0;
	while (av[i])
	{
		new_size += count_delimiters(av[i], '^');
		new_size += 1;
		i++;
	}
	return (new_size);
}

bool	is_redirection(char *s)
{
	if (!ft_strcmp(s, "<") || !ft_strcmp(s, "<<") || \
		!ft_strcmp(s, ">") || !ft_strcmp(s, ">>"))
		return (true);
	return (false);
}

bool	is_ptyin_interactive(char *cmd)
{
	if (!cmd || !cmd[0])
		return (false);
	return (!strcmp(cmd, "cat") || !strcmp(cmd, "more") || \
			!strcmp(cmd, "less") || !strcmp(cmd, "vim") || \
			!strcmp(cmd, "nano") || !strcmp(cmd, "vi") || \
			!strcmp(cmd, "read") || !strcmp(cmd, "top") || \
			!strcmp(cmd, "htop") || !strcmp(cmd, "passwd") || \
			!strcmp(cmd, "man") || !strcmp(cmd, "ssh") || \
			!strcmp(cmd, "su") || !strcmp(cmd, "sudo") || \
			!strcmp(cmd, "gdb") || !strcmp(cmd, "ftp") || \
			!strcmp(cmd, "sftp") || !strcmp(cmd, "mysql") || \
			!strcmp(cmd, "psql") || !strcmp(cmd, "telnet") || \
			!strcmp(cmd, "bash") || !strcmp(cmd, "sh") || \
			!strcmp(cmd, "zsh") || !strcmp(cmd, "scp") || \
			!strcmp(cmd, "python") || !strcmp(cmd, "node"));
}

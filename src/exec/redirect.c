/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:07:00 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/26 19:31:27 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirection(char *file, int flags, int std_fd)
{
	int	fd;

	fd = open(file, flags, 0644);
	{
		perror("open");
		return (-1);
	}
	if (dup2(fd, std_fd) == -1)
	{
		perror("dup2");
		return (-1);
	}
	close(fd);
	return (0);
}

int	do_redirection(char **av)
{
	(void) *(*av);
	return (0);
}

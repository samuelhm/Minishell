/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:09:34 by linyao            #+#    #+#             */
/*   Updated: 2024/08/26 13:28:57 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	ft_free(char **storage)
{
	if (storage && *storage)
	{
		free(*storage);
		*storage = NULL;
	}
}

char	*ft_extract_line(char **storage)
{
	size_t	i;
	char	*line;
	char	*temp;

	i = 0;
	while ((*storage)[i] && (*storage)[i] != '\n')
		i++;
	if ((*storage)[i] == '\n')
	{
		line = ft_strndup(*storage, i + 1);
		temp = ft_strdup1(*storage + i + 1);
		ft_free(storage);
		*storage = temp;
		if (**storage == '\0')
			ft_free(storage);
	}
	else
	{
		line = ft_strdup1(*storage);
		ft_free(storage);
	}
	return (line);
}

int	ft_read_file(int fd, char **storage)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		ft_free(storage);
		return (bytes_read);
	}
	if (bytes_read == 0)
		return (bytes_read);
	buffer[bytes_read] = '\0';
	if (*storage)
	{
		temp = ft_strjoin1(*storage, buffer);
		ft_free(storage);
		*storage = temp;
	}
	else
		*storage = ft_strdup1(buffer);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		ft_free(&storage);
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr1(storage, '\n'))
		bytes_read = ft_read_file(fd, &storage);
	if ((bytes_read == 0 && (!storage || *storage == '\0'))
		|| (bytes_read < 0))
	{
		ft_free(&storage);
		return (NULL);
	}
	line = ft_extract_line(&storage);
	return (line);
}

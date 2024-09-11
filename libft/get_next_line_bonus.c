/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:28:47 by linyao            #+#    #+#             */
/*   Updated: 2024/08/26 13:35:13 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
		temp = ft_strdupx(*storage + i + 1);
		ft_free(storage);
		*storage = temp;
		if (**storage == '\0')
			ft_free(storage);
	}
	else
	{
		line = ft_strdupx(*storage);
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
		temp = ft_strjoinx(*storage, buffer);
		ft_free(storage);
		*storage = temp;
	}
	else
		*storage = ft_strdupx(buffer);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*storage[FOPEN_MAX];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE <= 0)
	{
		if (fd >= 0 && fd < FOPEN_MAX)
			ft_free(&storage[fd]);
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchrx(storage[fd], '\n'))
		bytes_read = ft_read_file(fd, &storage[fd]);
	if ((bytes_read == 0 && (!storage[fd] || *storage[fd] == '\0'))
		|| (bytes_read < 0))
	{
		ft_free(&storage[fd]);
		return (NULL);
	}
	line = ft_extract_line(&storage[fd]);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	char	*line;
	int	i;
	int	fd1;
	int	fd2;
	int	fd3;

	fd1 = open("main.c", O_RDONLY);
	fd2 = open("test1.txt", O_RDONLY);
	fd3 = open("test3.txt", O_RDONLY);
	i = 1;
	while (i < 43)
	{
		line = get_next_line(fd1);
		printf("line%02d of main.c: %s", i, line);
		if (line == NULL)
                        printf("\n");
		free(line);
		line = get_next_line(fd2);
                printf("line%02d of test1.txt: %s", i, line);
		if (line == NULL)
			printf("\n");
                free(line);
		line = get_next_line(fd3);
                printf("line%02d of test3.txt: %s", i, line);
		if (line == NULL)
                        printf("\n");
                free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
*/

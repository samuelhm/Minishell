/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:04:44 by linyao            #+#    #+#             */
/*   Updated: 2024/08/26 13:29:33 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
int		ft_read_file(int fd, char **storage);
char	*ft_extract_line(char **storage);
void	ft_free(char **storage);
size_t	ft_strlen1(char *str);
char	*ft_strchr1(char *str, char c);
char	*ft_strjoin1(char *s1, char *s2);
char	*ft_strdup1(char *s);
char	*ft_strndup(char *s, size_t n);

#endif

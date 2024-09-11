/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:23:11 by linyao            #+#    #+#             */
/*   Updated: 2024/08/26 13:33:48 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

char	*get_next_line(int fd);
int		ft_read_file(int fd, char **storage);
char	*ft_extract_line(char **storage);
void	ft_free(char **storage);
size_t	ft_strlenx(char *str);
char	*ft_strchrx(char *str, char c);
char	*ft_strjoinx(char *s1, char *s2);
char	*ft_strdupx(char *s);
char	*ft_strndup(char *s, size_t n);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_chr1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:44:46 by linyao            #+#    #+#             */
/*   Updated: 2024/09/19 17:34:55 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"

bool	append_char(char **arr, char c);
{
	char	*new_arr;

	if (!*arr)
	{
		*arr = malloc(sizeof(char) * 2);
		if (!*arr)
			return (false);
		(*arr)[0] = c;
		(*arr)[1] = '\0';
		return (true);
	}
	new_arr = (char *)ft_realloc(*arr, ft_strlen(*arr) + 1, \
								ft_strlen(*arr) + 2);
	if (!new_arr)
		return (false);
	new_arr[ft_strlen(*arr)] = c;
	new_arr[ft_strlen(*arr) + 1] = '\0';
	*arr = new_arr;
	return (true);
}

bool	is_ordinary(char c)
{
	if (c != ' ' && c != MORE && c != LESS && c != PIPE \
					&& c != S_QUOTE && c != D_QUOTE)
		return (true);
	return (false);
}

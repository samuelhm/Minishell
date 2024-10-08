/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_chr1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:44:46 by linyao            #+#    #+#             */
/*   Updated: 2024/10/08 11:50:34 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	append_char(char **arr, char c)
{
	char	*new_arr;
	size_t	arr_len;

	if (!*arr)
	{
		*arr = malloc(sizeof(char) * 2);
		if (!*arr)
			return (false);
		(*arr)[0] = c;
		(*arr)[1] = '\0';
		return (true);
	}
	arr_len = ft_strlen(*arr);
	new_arr = (char *)ft_realloc(*arr, arr_len + 1, \
					arr_len + 2);
	if (!new_arr)
		return (false);
	new_arr[arr_len] = c;
	new_arr[arr_len + 1] = '\0';
	*arr = new_arr;
	return (true);
}

bool	is_ordinary(char c)
{
	if (c != ' ' && c != '\t' && c != MORE && c != LESS && c != PIPE \
					&& c != S_QUOTE && c != D_QUOTE)
		return (true);
	return (false);
}

void	initarrays(char **new_arr, char ***new_array)
{
	*new_arr = NULL;
	*new_array = NULL;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_chr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:36:43 by linyao            #+#    #+#             */
/*   Updated: 2024/09/17 17:19:51 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/env.h"

void	handle_special(char ***array, char **arr, char **c)
{
	if (**c == MORE || **c == LESS || **c == PIPE)
	{
		update_array(array, arr);
		if (**c == MORE && *(*c + 1) == MORE)
		{
			add_array(array, DOUBLE_MORE);
			(*c)++;
			return ;
		}
		if (**c == LESS && *(*c + 1) == LESS)
		{
			add_array(array, DOUBLE_LESS);
			(*c)++;
			return ;
		}
		if (**c == MORE)
			add_array(array, MORE_S);
		if (**c == LESS)
			add_array(array, LESS_S);
		if (**c == PIPE)
			add_array(array, PIPE_S);
	}
}

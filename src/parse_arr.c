/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:22:27 by linyao            #+#    #+#             */
/*   Updated: 2024/09/17 17:28:50 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../env/env.h"

void	update_array(char ***array, char **arr)
{
	if (!*arr)
		return ;
	if (**arr)
		add_array(array, *arr);
	free(*arr);
	*arr = NULL;
}

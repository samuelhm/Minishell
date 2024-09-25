/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 17:02:43 by linyao            #+#    #+#             */
/*   Updated: 2024/09/25 17:13:13 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/env.h"
#include "../../inc/minishell.h"

// extract the infile part from the two-dimensional array
// remove the element about infile from the array
char	**get_infile_path(char ***av)
{
	int		i;
	char	**res;

	i = 0;
	res = NULL;
	if (!*av || !**av)
		return (NULL);
	while ((*av)[i])
	{
		assign_infile(av, &res, &i);
		i++;
	}
	delete_infile_element(av, res);
	return (res);
}

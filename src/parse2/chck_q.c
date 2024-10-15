/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chck_q.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:04:52 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/15 22:15:40 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	get_first_quote(char *s)
{
	while (*s)
	{
		if (*s == D_QUOTE)
			return (D_QUOTE);
		if (*s == S_QUOTE)
			return (S_QUOTE);
		s++;
	}
	return (0);
}

//check if first quote is closed
bool	check_p2quotes(char *s)
{
	char	*init;
	char	*final;
	char	first;

	if (!strchr(s, '\'') && !strchr(s, '\"'))
		return (true);
	first = get_first_quote(s);
	if (!first)
		return (false);
	init = strchr(s, first);
	if (*(init + 1) == '\0')
		return (false);
	final = strchr(init + 1, first);
	if (final == NULL || final == init)
		return (false);
	if (*(final + 1) != '\0')
		return (check_p2quotes(final + 1));
	else
		return (true);
}

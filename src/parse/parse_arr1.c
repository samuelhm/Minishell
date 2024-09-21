/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arr1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:03:37 by linyao            #+#    #+#             */
/*   Updated: 2024/09/21 21:54:09 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/env.h"

//To remove the quotes in the elements of two-dimensional arrays
static void	process_quote(char **s, char **new)
{
	(*s)++;
	while (**s != S_QUOTE && **s != D_QUOTE)
		append_char(new, *(*s)++);
	(*s)++;
}

//To deal with the case there is $ syntax without any quote
//Space is passed as parameter marking no quotes
//The case with $ in double quotes has been handle before
static void	process_ordinary(char **s, t_hash *env, char **new)
{
	if (**s == '$' && *(*s + 1) && *(*s + 1) != '$')
		check_handle_dollar(new, s, ' ');
	else
		append_char(new, **s);
	(*s)++;
}

static char	*process_analyze(char *s, t_hash *env)
{
	char	*new;

	new = NULL;
	while (*s)
	{
		if (*s == S_QUOTE || *s == D_QUOTE)
			process_quote(&s, &new);
		else
			process_ordinary(&s, env, &new);
	}
	if (!new)
		append_char(&new, '\0');
	return (new);
}

char	**process_av(char **av, t_hash *env)
{
	int		i;
	char	*str_pro;
	char	**res;

	i = 0;
	res = NULL;
	if (!av || !*av)
		return (NULL);
	while (av[i])
	{
		if (!ft_strcmp(av[i], "\'\'") && !ft_strcmp(av[i], "\"\""))
		{
			str_pro = process_analyze(av[i], env);
			add_array(&res, str_pro);
			free(str_pro);
			str_pro = NULL;
		}
		else
			add_array(&res, "\0");
		i++;
	}
	free_array(av);
	return (res);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arr1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:03:37 by linyao            #+#    #+#             */
/*   Updated: 2024/10/14 12:04:16 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//To remove the quotes in the elements of two-dimensional arrays
static void	process_quote(char **s, char **new)
{
	(*s)++;
	while (**s && **s != S_QUOTE && **s != D_QUOTE)
		append_char(new, *(*s)++);
	if (**s == S_QUOTE || **s == D_QUOTE)
		(*s)++;
}

//To deal with the case there is $ syntax without any quote
//Space is passed as parameter marking no quotes
//The case with $ in double quotes has been handle before
static void	process_ordinary(char **s, t_hash *env, char **new)
{
	if (**s == '$' && *(*s + 1) && *(*s + 1) != '$')
		check_handle_dollar(env, new, s, ' ');
	else
		append_char(new, **s);
	if (**s)
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
		if (ft_strcmp(av[i], "\'\'") != 0 && ft_strcmp(av[i], "\"\"") != 0)
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

void	handle_quote_first(t_hash *env, char ***array, char **arr, char **c)
{
	char	ch;

	if (**c == S_QUOTE)
		ch = S_QUOTE;
	else if (**c == D_QUOTE)
		ch = D_QUOTE;
	else
		return ;
	if (*arr != NULL)
		store_to_array(array, arr);
	append_char(arr, **c);
	(*c)++;
	while (**c && **c != ch)
		check_handle_dollar(env, arr, c, ch);
	append_char(arr, **c);
	(*c)++;
	if (*(*c) && *(*c) == ' ' && *arr != NULL)
		store_to_array(array, arr);
}

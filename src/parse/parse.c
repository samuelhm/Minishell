/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:20:41 by linyao            #+#    #+#             */
/*   Updated: 2024/10/16 04:36:41 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	handle_single(bool *s_close, bool *d_close, int *flag)
{
	if (*flag == DOUBLE_QUOTE)
	{
		*flag = SINGLE_QUOTE;
		if (!*d_close && !*s_close)
			return (false);
		else if (*d_close && !*s_close)
			*s_close = true;
		else if (*s_close)
			*s_close = false;
	}
	else if (*flag == SINGLE_QUOTE)
		*s_close = !*s_close;
	else if (*flag == 0)
	{
		*flag = SINGLE_QUOTE;
		*s_close = false;
	}
	return (true);
}

bool	handle_double(bool *s_close, bool *d_close, int *flag)
{
	if (*flag == SINGLE_QUOTE)
	{
		*flag = DOUBLE_QUOTE;
		if (!*s_close && !*d_close)
			return (false);
		else if (*s_close && !*d_close)
			*d_close = true;
		else if (*d_close)
			*d_close = false;
	}
	else if (*flag == DOUBLE_QUOTE)
		*d_close = !*d_close;
	else if (*flag == 0)
	{
		*flag = DOUBLE_QUOTE;
		*d_close = false;
	}
	return (true);
}

bool	check_quote(char *s)
{
	bool	single_quote_close;
	bool	double_quote_close;
	int		flag;

	single_quote_close = true;
	double_quote_close = true;
	flag = 0;
	while (*s)
	{
		if (*s == '\'')
		{
			if (!handle_single(&single_quote_close, &double_quote_close, &flag))
				return (false);
		}
		else if (*s == '\"')
		{
			if (!handle_double(&single_quote_close, &double_quote_close, &flag))
				return (false);
		}
		s++;
	}
	return (single_quote_close && double_quote_close);
}

void	split_into_arrays(t_hash *env, char ***new, char *input, int i)
{
	char	*str;
	char	*new_arr;
	char	**new_array;

	initarrays(&new_arr, &new_array);
	if (!input || !new)
		return ;
	str = ft_strtrim(input, " \t");
	input = str;
	while (*str)
	{
		renovar_array(&new_array, &new_arr, &str);
		handle_special(&new_array, &new_arr, &str);
		if (!i++)
			handle_quote_first(env, &new_array, &new_arr, &str);
		else
			handle_quote(env, &new_array, &new_arr, &str);
		if (is_ordinary(*str))
			append_char(&new_arr, *str);
		if (*str && *str != '\'' && *str != '\"')
			str++;
	}
	store_to_array(&new_array, &new_arr);
	*new = new_array;
	free(input);
}

char	**split_av(t_hash *env, char *input)
{
	char	**new;

	if (!input || !input[0])
		return (NULL);
	if (!check_quote(input))
	{
		perror("These quotes don't match.");
		return (NULL);
	}
	new = NULL;
	split_into_arrays(env, &new, input, 0);
	if (!is_compliance(new))
		return (free_array(new), NULL);
	return (new);
}

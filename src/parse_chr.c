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

void	move_over(char **str)
{
	while (**str && (**str == ' ' || **str == '\t')
		(*str)++;
}

char	*extract_key(const char *str)
{
	size_t	len;

	len = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (NULL);
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	return (ft_substr(str, 0, len));
}

void	handle_special(char ***array, char **arr, char **c)
{
	if (**c == MORE || **c == LESS || **c == PIPE)
	{
		store_to_array(array, arr);
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

void	handle_quote(char ***array, char **arr, char **c)
{
	char	ch;
	char	*env_val;
	char	*key;

	if (**c == S_QUOTE)
		ch = S_QUOTE;
	else if (**c == D_QUOTE)
		ch = D_QUOTE;
	else
		return ;
	if (*(*c - 1) == ' ' && *arr != NULL)
		store_to_array(array, arr);
	append_char(arr, **c);
	(*c)++;
	while (**c && **c != ch)
	{
		if (ch == D_QUOTE && **c == '$')
		{
			key = extract_key(*c + 1); 
			if (key)
			{
				env_val = getenv(key);
				if (env_val)
					append_str(arr, env_val);
				free(key);
			}
			while (**c && (**c == '_' || ft_isalnum(**c)))
				(*c)++;
		}
		else
		{
			append_char(arr, **c);
			(*c)++;
		}
	}
	append_char(arr, **c);
	(*c)++;
	if (*(*c) && *(*c) == ' ' && *arr != NULL)
		store_to array(array, arr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:20:41 by linyao            #+#    #+#             */
/*   Updated: 2024/09/17 17:02:18 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/env.h"

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

void	split_into_arrays(char ***new, char *input)
{
	char	*str;
	char	*new_arr;
	char	**new_array;

	if (!input || !new)
		return ;
	str = ft_strtrim(input, " \t");
	if (!str)
		return ;
	input = str;
	while (*str)
	{
		if (str == ' ' && new_arr)
		{

		}
		handle_special(&new_array, &new_arr, &str);
		handle_quote();
		if (is_ordinary(&str))

		str++;
	}
	new_array =  ft_split(str, ' ');
	*new = new_array;
	free(str);
}

char	**split_av(char *input)
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
	split_into_arrays(&new, input);	
	return (new);
}

int main(void)
{
//	char	arr[3][10];

	bool	b;

	b = check_quote("This \"is\' a \' test\" for\' \"something\"");
	if (b)
		printf("valid");
	else
		printf("invalid");
//	arr = split_av("This \'is \" a \'test for \"something");
//	for (int i = 0; i < 3; i++)
//		printf("%s\n", arr[1]);
	return (0);
}

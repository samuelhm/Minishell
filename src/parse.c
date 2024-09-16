/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:20:41 by linyao            #+#    #+#             */
/*   Updated: 2024/09/16 18:31:24 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/env.h"

bool	check_quote(char *s)
{
	while (*s)
	{
		if (*s == '\'')
		{
			s++;
			while (*s && *s != '\'')
				s++;
			if (*s == '\0')
				return (false);
		}
		else if (*s == '\"')
		{
			s++;
			while (*s && *s != '\"')
				s++;
			if (*s == '\0')
				return (false);
		}
		s++;
	}
	return (true);
}

bool    check_quote(char *s)
{
	bool	single_quote_close = true;
	bool	double_quote_close = true;
	int	flag = 0;

	while (*s)
	{
		if (*s == '\'')
		{
			if (flag == DOUBLE_QUOTE && double_quote_close == false)
				break ;
			else if (flag == DOUBLE_QUOTE && double_quote_close == true)
			{
				flag = SINGLE_QUOTE;
				if (single_quote_close == false)
					single_quote_close = true;
				else if (single_quote_close == true)
					single_quote_close = false;
			}
			else if (flag == SINGLE_QUOTE && single_quote_close == false)
				single_quote_close = true;
			else if (flag == SINGLE_QUOTE && single_quote_close == true)
				single_quote_close = false;
			else if (flag == 0)
			{
				flag = SINGLE_QUOTE;
				single_quote_close = false;
			}
		}
		else if (*s == '\"')
		{
			if (flag == SINGLE_QUOTE && single_quote_close == false)
				break ;
			else if (flag == SINGLE_QUOTE && single_quote_close == true)
			{
				flag = DOUBLE_QUOTE;
				if (double_quote_close == false)
					double_quote_close = true;
				else if (double_quote_close == true)
					double_quote_close = false;
			}
			else if (flag == DOUBLE_QUOTE && double_quote_close == false)
				double_quote_close = true;
			else if (flag == DOUBLE_QUOTE && double_quote_close == true)
				double_quote_close = false;
			else if (flag == 0)
			{
				flag = DOUBLE_QUOTE;
				double_quote_close = false;
			}
		}
		s++;
	}
	return (single_quote_close && double_quote_close);
}

void	split_into_arrays(char ***new, char *input)
{
	char	*str;
	char	**new_array;

	if (!input || !new)
		return ;
	str = ft_strtrim(input, " \t");
	if (!str)
		return ;
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
	char	arr[3][10];

	arr = split_av("This \'is \" a \'test for \"something");
	for (int i = 0; i < 3; i++)
		printf("%s\n", arr[1]);
	return (0);
}

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 02:58:49 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/16 03:26:37 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_tokens(char *input, int i, int count)
{
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == '\0')
			break ;
		if ((input[i] == '>' && input[i + 1] == '>') || \
			(input[i] == '<' && input[i + 1] == '<'))
			i += 2;
		else if (is_separator(input[i]))
			i++;
		else
		{
			while (input[i] && !is_separator(input[i]))
				i++;
		}
		count++;
	}
	return (count);
}

int	handle_compound_operator(char **tokens, char *input, int i, int *j)
{
	tokens[*j] = strndup(input + i, 2);
	if (!tokens[*j])
		return (-1);
	(*j)++;
	return (i + 2);
}

int	handle_simple_operator(char **tokens, char *input, int i, int *j)
{
	tokens[*j] = strndup(input + i, 1);
	if (!tokens[*j])
		return (-1);
	(*j)++;
	return (i + 1);
}

int	handle_word(char **tokens, char *input, int i, int *j)
{
	int		start;
	char	quote;

	start = i;
	quote = 0;
	while (input[i])
	{
		if (quote == 0 && (input[i] == '\'' || input[i] == '\"'))
			quote = input[i];
		else if (quote != 0 && input[i] == quote)
			quote = 0;
		else if (quote == 0 && (is_separator(input[i]) || input[i] == ' '))
			break ;
		i++;
	}
	tokens[*j] = strndup(input + start, i - start);
	if (!tokens[*j])
		return (-1);
	(*j)++;
	return (i);
}

char	**split_input(char *input, int i, int j)
{
	char	**tokens;
	int		num_tokens;

	num_tokens = count_tokens(input, 0, 0);
	tokens = malloc(sizeof(char *) * (num_tokens + 1));
	if (!tokens)
		return (NULL);
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		if (input[i] == '\0')
			break ;
		if ((input[i] == '>' && input[i + 1] == '>') || \
			(input[i] == '<' && input[i + 1] == '<'))
			i = handle_compound_operator(tokens, input, i, &j);
		else if (is_separator(input[i]))
			i = handle_simple_operator(tokens, input, i, &j);
		else
			i = handle_word(tokens, input, i, &j);
		if (i == -1)
			return (free_newav(tokens, j));
	}
	tokens[j] = NULL;
	return (tokens);
}

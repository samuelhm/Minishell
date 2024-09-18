/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:22:27 by linyao            #+#    #+#             */
/*   Updated: 2024/09/17 17:28:50 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../env/env.h"

void	store_to_array(char ***array, char **arr)
{
	if (!*arr)
		return ;
	if (**arr)
		add_array(array, *arr);
	free(*arr);
	*arr = NULL;
}

//To append a string to a two-dimensional array
//Every element in the two-dimensional array is a parsed unit of 
//a shell command line
bool	add_array(char ***array, char *s)
{
	int	count;
	char	**new_arrays;

	count = 0;
	if (!*array)
	{
		*array = malloc(sizeof(char *) * 2);
		if (!*array)
			return (false);
		(*array)[0] = ft_strdup(s);
		(*array)[1] = NULL;
		return (true);
	}
	while ((*array)[count])
		count++;
	new_arrays = ft_realloc(*array, sizeof(char *) * (count + 1), \
				sizeof(char *) * (count + 2));
	if (!new_array)
		return (false);
	*array = new_arrays;
	(*array)[count] = ft_strdup(s);
	(*array)[count + 1] = NULL;
	return (true);
}

//To append a string to an original one-demensional string array, such as
//appending the environment variables to array
void	append_str(char **arr, char *env_val)
{
	size_t	arr_len;
	size_t	env_val_len;
	size_t	new_len;
	char	*new_arr;

	arr_len = ft_strlen(*arr);
	env_val_len = ft_strlen(env_val);
	new_len = arr_len + env_val_len;
	new_arr = (char *)realloc(*arr, arr_len, new_len + 1);
	if (!new_arr)
		return ;
	ft_memcpy(new_arr + arr_len, env_val, env_val_len);
	new_arr[new_len] = '\0';
	*arr = new_arr;
}

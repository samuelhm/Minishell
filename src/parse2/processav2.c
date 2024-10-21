/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processav2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:35:24 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/21 20:11:53 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_fquotes(char **s, int i, int j)
{
	char	tmp[900];
	bool	q;
	char	qc;

	qc = 0;
	q = false;
	while ((*s)[i])
	{
		if (((*s)[i] == '\'' && (qc == 0 || qc == '\'')) || \
			((*s)[i] == '\"' && (qc == 0 || qc == '\"')))
		{
			if (q == false)
				qc = (*s)[i];
			else if (qc == (*s)[i])
				qc = 0;
			q = !q;
			i++;
			continue ;
		}
		tmp[j++] = (*s)[i++];
	}
	tmp[j] = '\0';
	free(*s);
	*s = ft_strdup(tmp);
}

void	check_fquotes(char **av)
{
	int		i;

	i = 0;
	while (av[i])
	{
		if (strchr(av[i], '\'') || strchr(av[i], '\"'))
			remove_fquotes(&av[i], 0, 0);
		i++;
	}
}

//void	move_av(char **av)
//{
//	int		i;
//	int		j;
//
//	i = 0;
//	j = 0;
//	while (av[i])
//	{
//		if (av[i][0] != '\0')
//		{
//			av[j] = av[i];
//			j++;
//		}
//		else
//			free(av[i]);
//		i++;
//	}
//	av[j] = NULL;
//}

char	**process(char **av, t_hash *env)
{
	char	**new_av;

	new_av = NULL;
	if (!all_quote_ok(av))
	{
		free_array(av);
		return (NULL);
	}
	expand_dolar(av, env);
	check_fquotes(av);
	new_av = create_new_av(av, 0, 0, 0);
	if (!new_av)
	{
		free_array(av);
		return (NULL);
	}
	free_array(av);
	if (!new_av[0] && new_av)
	{
		free(new_av);
		new_av = NULL;
	}
	return (new_av);
}

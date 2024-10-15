/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processav2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:35:24 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/16 00:48:00 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	all_quote_ok(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (!check_p2quotes(av[i]))
		{
			perror("ERROR, no se aceptan comillas abiertas\n");
			return (false);
		}
		i++;
	}
	return (true);
}

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
			qc = (*s)[i];
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

char	**create_new_av(char **av)
{
	int		i;
	int		j;
	char	**new_av;
	char	*pos;

	// Primer paso: calcular el tamaño que tendrá new_av
	int		new_size = 0;
	for (i = 0; av[i]; i++)
	{
		pos = strchr(av[i], '^');
		if (pos)
			new_size += 2;  // Si encontramos ^, añadimos 2 elementos
		else
			new_size += 1;  // Si no, solo añadimos 1
	}

	// Asignar memoria para new_av con el tamaño correcto
	new_av = malloc(sizeof(char *) * (new_size + 1));  // +1 para NULL al final
	if (!new_av)
		return (NULL);

	// Segundo paso: llenar new_av
	j = 0;
	for (i = 0; av[i]; i++)
	{
		pos = strchr(av[i], '^');
		if (!pos)
		{
			// Si no hay ^, copiamos la cadena tal cual
			new_av[j] = strdup(av[i]);
			if (!new_av[j])
				return (NULL);  // Manejar el error de asignación de memoria
			j++;
		}
		else
		{
			// Si hay ^, dividimos la cadena en dos
			int len_before = pos - av[i];  // Longitud antes de ^
			new_av[j] = strndup(av[i], len_before);  // Copiar parte antes de ^
			if (!new_av[j])
				return (NULL);  // Manejar el error de asignación de memoria
			j++;

			// Copiar la parte después de ^
			new_av[j] = strdup(pos + 1);
			if (!new_av[j])
				return (NULL);  // Manejar el error de asignación de memoria
			j++;
		}
	}
	new_av[j] = NULL;  // Terminar el array con NULL

	return (new_av);
}

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
	new_av = create_new_av(av);
	if (!new_av)
	{
		perror("Error creando new_av");
		free_array(av);
		return (NULL);
	}
	free_array(av);
	return (new_av);
}

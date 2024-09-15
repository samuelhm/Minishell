/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:22:32 by linyao            #+#    #+#             */
/*   Updated: 2024/09/14 13:21:03 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../lib/libft/libft.h"
# include "minishell.h"

# define HASH_LEN 300


typedef struct s_node
{
	char			*key;
	char			*value;
	struct	s_node	*next;
}		t_node;

typedef struct s_hash
{
	t_node	*slot[HASH_LEN];
}		t_hash;

t_hash  *init_hash(void);
char    *lookup_hash(t_hash *env, char *key);
bool    assign_hash(t_hash *en, char *key, char *value);
unsigned int    hash_function(char *key);
t_node  *init_list(void);
bool    add_list(t_node *n, char *key, char *value);
bool    del_list(t_node *n, char *key);
bool    del_hash(t_hash *env, char *key);

#endif

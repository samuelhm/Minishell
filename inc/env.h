/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:22:32 by linyao            #+#    #+#             */
/*   Updated: 2024/09/17 17:18:10 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../lib/libft/libft.h"
# include "minishell.h"

# define HASH_LEN 300
# define SINGLE_QUOTE 1
# define DOUBLE_QUOTE 2
# define MORE '>'
# define LESS '<'
# define PIPE '|'
# define S_QUOTE '\''
# define D_QUOTE '\"'
# define DOUBLE_MORE ">>"
# define DOUBLE_LESS "<<"
# define MORE_S ">"
# define LESS_S "<"
# define PIPE_S "|"

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

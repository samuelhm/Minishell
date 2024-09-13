/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linyao <linyao@student.42barcelona.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:22:32 by linyao            #+#    #+#             */
/*   Updated: 2024/09/13 16:03:52 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../lib/libft/libft.h" 

# define HASH_LEN 300;


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

#endif

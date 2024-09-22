/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:14:45 by linyao            #+#    #+#             */
/*   Updated: 2024/09/22 13:21:52 by linyao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdlib.h>
# include "../lib/libft/libft.h"
# include "env.h"

# define PROMPT "\x1b[1;32mminishell\x1b[0m\x1b[1;36m > \x1b[0m"
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

struct s_hash;

typedef struct s_ms
{
	char			**av;
	struct s_hash	*env;
}	t_ms;

void	init_ms(t_ms *ms, char **env);
void    init_env(t_ms *ms, char **env);
void    realize_shell(t_ms *ms);

//------------------parse------------------
bool    handle_single(bool *s_close, bool *d_close, int *flag);
bool    handle_double(bool *s_close, bool *d_close, int *flag);
bool    check_quote(char *s);
void    split_into_arrays(struct s_hash *env, char ***new, char *input);
char    **split_av(struct s_hash *env, char *input);
void    store_to_array(char ***array, char **arr);
bool    add_array(char ***array, char *s);
bool    append_str(char **arr, char *env_val);
bool	append_char(char **arr, char c);
void    move_over(char **str);
char    *extract_key(const char *str);
void    handle_special(char ***array, char **arr, char **c);
void    handle_quote(struct s_hash *env, char ***array, char **arr, char **c, char *start);
bool    is_ordinary(char c);
bool    is_compliance(char **arrays);
void    free_array(char **arrays);
int     count_arrays(char **arrays);
char    **process_av(char **av, struct s_hash *env);
void    check_handle_dollar(struct s_hash *env, char **arr, char **c, char ch);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:14:45 by linyao            #+#    #+#             */
/*   Updated: 2024/10/01 09:56:13 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdlib.h>
# include "libft.h"
# include <limits.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "env.h"
# include <fcntl.h>
# include <signal.h>
# include <termios.h>

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

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define NORMAL 1
# define INTERACTIVE 2

struct	s_hash;

typedef struct s_ms
{
	char			**av;
	struct s_hash	*env;
	char			**inf;
	char			**outf;
}	t_ms;

void	init_ms(t_ms *ms, char **env);
void	init_env(t_ms *ms, char **env);
void	realize_shell(t_ms *ms);

//-------------------env-------------------
char	**get_env_arr(t_ms *ms);

//------------------parse------------------
bool	handle_single(bool *s_close, bool *d_close, int *flag);
bool	handle_double(bool *s_close, bool *d_close, int *flag);
bool	check_quote(char *s);
void	split_into_arrays(t_hash *env, char ***new, char *input);
char	**split_av(t_hash *env, char *input);
void	store_to_array(char ***array, char **arr);
bool	add_array(char ***array, char *s);
bool	append_str(char **arr, char *env_val);
bool	append_char(char **arr, char c);
void	move_over(char **str);
char	*extract_key(const char *str);
void	handle_special(char ***array, char **arr, char **c);
void	handle_quote(t_hash *env, char ***array, char **arr, char **c, char *start);
bool	is_ordinary(char c);
bool	is_compliance(char **arrays);
void	free_array(char **arrays);
int		count_arrays(char **arrays);
char	**process_av(char **av, struct s_hash *env);
void	check_handle_dollar(t_hash *env, char **arr, char **c, char ch);
char	**get_infile_path(char ***av);

//Utils
bool	is_special(const char *s);
char	**get_env_arr(t_ms *ms);
void	show_debug(t_ms *ms);
void	free_env_arr(char **env);

//Built-ins
int		blt_echo(char **av);
int		blt_exit(t_ms *ms);
int		blt_cd(char **av, t_hash *env);
int		blt_pwd(void);
int		blt_export(char **av, t_hash *env);
int		blt_unset(char **av, t_hash *env);
int		blt_env(t_hash *env);

//Exec
int		process_line(t_ms *ms);
bool	has_in_redirect(char **av);
bool	has_out_redirect(char **av);
bool	has_pipe(char **av);
bool	has_any_redirect(char **av);
int		do_redirection(char **av);
bool	is_builtin(char **av);
int		exec_builtin(t_ms *ms);
int		execute_command(char *path, char **args, char **env);

//Signals
int		init_signals(int mode);
void	do_sigign(int signum);
#endif

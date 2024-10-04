/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:14:45 by linyao            #+#    #+#             */
/*   Updated: 2024/10/04 20:49:35 by shurtado         ###   ########.fr       */
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
	char			**crude_env;
	int				last_pid;
	int				status;
	int				**fd_pipe;
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
void	delete_env(t_hash *env);
void	free_resources(t_ms *ms, int result);
void	process_cmds(t_ms *ms);
void	remove_redirections(char **av);

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
bool	is_builtin(char *cmd);
int		exec_builtin(char **cmd, t_hash *env);
char	*getpath(t_hash *env, char *file);
char	*get_filename(char **av, char *redir);
void	execute_simple_comand(t_ms *ms);

//Signals
void	init_signals(void);
void	set_child_signals(void);

//PIPE
void	init_pipes(t_ms *ms);
void	clean_pipes(int **fd_pipe);
bool	has_redirection(char **av, char *redir);
void	process_pipe(int fd_pipe[2], int is_last, int fd_local[2]);
void	execute_command(t_ms *ms, int fd_in, int fd_out, char **cmd);
char	**get_cmd(t_ms *ms);
bool	setup_redirections(t_ms *ms);
int		wait_for_last_process(t_ms *ms);
bool	handle_input_redirection(char **av);
bool	handle_output_trunc_redirection(char **av);
bool	handle_output_append_redirection(char **av);
bool	handle_heredoc_redirection(char **av);
int		handle_heredoc(char *delimiter);
#endif

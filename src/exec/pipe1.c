/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:17:43 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/22 00:34:31 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_child(char **cmd)
{
	if (!cmd || !cmd[0])
		exit(127);
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found.\n", 22);
	exit(127);
}

void	remove_redirections(char **av)
{
	int		i;
	int		j;

	i = 0;
	while (av[i] && ft_strcmp(av[i], PIPE_S) != 0)
	{
		if (is_special(av[i]))
		{
			j = i;
			free(av[i]);
			free(av[i + 1]);
			while (av[j + 2])
			{
				av[j] = av[j + 2];
				j++;
			}
			av[j] = NULL;
			av[j + 1] = NULL;
		}
		else
			i++;
	}
}

void	wait_for_processes(t_list *pidlst, int *status)
{
	t_list	*node;

	node = pidlst;
	while (node)
	{
		waitpid((pid_t)(intptr_t)node->content, status, 0);
		node = node->next;
	}
}

void	restore_std_fds(t_ms *ms)
{
	if (!isatty(STDIN_FILENO))
		dup2(ms->atty_in, STDIN_FILENO);
	if (!isatty(STDOUT_FILENO))
		dup2(ms->atty_out, STDOUT_FILENO);
}

void	handle_builtin(t_ms *ms, char **cmd)
{
	if (!setup_redirections(cmd, STDIN_FILENO, STDOUT_FILENO))
	{
		ms->status = 1;
		perror("Redirection ERR");
	}
	else
	{
		remove_redirections(cmd);
		ms->status = exec_builtin(cmd, ms->env, &ms->crude_env);
	}
	restore_std_fds(ms);
}

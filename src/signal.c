/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:28:31 by shurtado          #+#    #+#             */
/*   Updated: 2024/10/19 00:05:03 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		printf("\n");
		rl_redisplay();
	}
}

void	handle_signal_b(int sig)
{
	if (sig == SIGINT)
		printf("\n");
}

void	set_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
}

void	init_signals(int mode)
{
	struct sigaction	sa;

	if (mode == NORMAL)
	{
		sa.sa_handler = handle_signal;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
	else if (mode == CHILD)
	{
		sa.sa_handler = handle_signal_b;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
		sa.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sa, NULL);
	}
}

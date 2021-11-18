/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lubourre <lubourre@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 18:25:03 by lubourre          #+#    #+#             */
/*   Updated: 2021/11/18 18:36:07 by lubourre         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_sigint(int osef)
{
	(void)osef;
	last_exit = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	if_sigheredoc(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_reset(int osef)
{
	(void)osef;
}

void	signal_handle(int pid)
{
	if (WIFSIGNALED(pid))
	{
		if (WTERMSIG(pid) == SIGQUIT)
		{
			printf("Quit: 3\n");
			last_exit = 131;
		}
		else
		{
			last_exit = 130;
			printf("\n");
		}
	}
}

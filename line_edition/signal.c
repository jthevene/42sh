/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <dvirgile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:42 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/13 12:13:13 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

void		ft_sigwinch(int sig)
{
	(void)sig;
	if (g_shell.current_line)
	{
		ioctl(0, TIOCGWINSZ, g_shell.win);
		print_line(ft_strlen(g_shell.current_line));
	}
}

void		ft_sigint(int sig)
{
	(void)sig;
	kill(-1, SIGCHLD);
	if (g_shell.running == 2)
	{
		ft_bzero(g_shell.current_line, ft_strlen(g_shell.current_line));
		ft_putstr("\n");
		ft_putstr(g_shell.prompt);
		tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
		g_shell.running = 0;
		return ;
	}
	reset_line();
	g_shell.curr_hist = g_shell.hist;
	g_shell.len = 0;
	if (!g_shell.running)
	{
		ft_putstr("\n\n");
		ft_putstr(g_shell.prompt);
		tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
	}
	g_shell.running = 0;
}

void		ft_sigkill(int sig)
{
	(void)sig;
	if (!((int)ft_strlen(g_shell.current_line)) && !kill(-1, SIGCHLD))
		ft_exit(NULL);
}

void		ft_signal(void)
{
	signal(SIGWINCH, ft_sigwinch);
	signal(SIGINT, ft_sigint);
}

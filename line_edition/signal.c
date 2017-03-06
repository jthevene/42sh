/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/02 15:18:58 by dvirgile          #+#    #+#             */
/*   Updated: 2017/03/06 14:09:44 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

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
		ft_exit();
}

void		ft_signal(void)
{
	signal(SIGWINCH, ft_sigwinch);
	signal(SIGINT, ft_sigint);
}

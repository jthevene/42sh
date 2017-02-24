/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 20:14:37 by sgaudin          ###   ########.fr       */
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
	reset_line();
	g_shell.curr_hist = g_shell.hist;
	g_shell.len = 0;
	ft_putstr("\n");
	display_prompt();
}

void		ft_sigkill(int sig)
{
	(void)sig;
	if (g_shell.current_line)
		ft_bzero(g_shell.current_line, g_shell.line_size -
				g_shell.prompt_len);
	if (g_shell.line_2d_x)
		ft_putstr("\n");
	ft_reset_termios(g_shell.t_back);
	ft_exit();
}

void		distrib_signals(int sig)
{
	if (sig == SIGWINCH)
		ft_sigwinch(sig);
	else if (sig == SIGINT)
		ft_sigint(sig);
}

void		ft_signal(void)
{
	FT_INIT(int, sig, 2);
	while (sig < 32)
	{
		signal(sig, distrib_signals);
		sig++;
	}
}

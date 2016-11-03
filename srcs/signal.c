/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 11:31:13 by jules             #+#    #+#             */
/*   Updated: 2016/10/25 16:09:30 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static void		ft_sigwinch(int sig)
{
	(void)sig;
	ioctl(0, TIOCGWINSZ, g_shell.win);
	//réafficher current_line correctement si c'etait sur plusieurs lignes
	print_line(ft_strlen(g_shell.current_line));
}

// static void		ft_sigint(int sig)
// {
// 	(void)sig;
// 	if (!g_shell.running)
// 	{
// 		ft_reset_termios(g_shell.t_back);
// 		signal(SIGTSTP, SIG_DFL);
// 		ioctl(0, TIOCSTI, "\032");
// 	}
// }

// static void		ft_sigtstp(int sig)
// {
// 	(void)sig;
// 	if (!g_shell.running)
// 	{
// 		ft_reset_termios(g_shell.t_back);
// 		signal(SIGTSTP, SIG_DFL);
// 		ioctl(0, TIOCSTI, "\032");
// 	}
// }

// static void		ft_sigcont(int sig)
// {
// 	(void)sig;
// 	init_termios(g_shell.my_termios);
// 	signal(SIGTSTP, ft_sigtstp);
// }

void			ft_signal(void)
{
	signal(SIGWINCH, ft_sigwinch);
	// signal(SIGTSTP, ft_sigtstp);
	// signal(SIGCONT, ft_sigcont);
	// signal(SIGINT, ft_sigint);
}
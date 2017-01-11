/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 11:31:13 by jules             #+#    #+#             */
/*   Updated: 2016/11/08 16:52:18 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

void		ft_sigwinch(int sig)
{
//	printf("\nsig winch=%d\n", sig);
	(void)sig;
	if (g_shell.current_line)
	{
		ioctl(0, TIOCGWINSZ, g_shell.win);
		print_line(ft_strlen(g_shell.current_line));
	}
}

 void		ft_sigint(int sig)  // ctrl + c
{
	(void)sig;
	go_to_end();
 	if (g_shell.current_line)
		ft_bzero(g_shell.current_line, g_shell.line_size - 3);
	ft_putstr("\n");
	display_prompt();
}

void 		ft_sigkill(int sig)
{
	(void)sig;
	if (g_shell.current_line)
		ft_bzero(g_shell.current_line, g_shell.line_size - 3);
	if (g_shell.line_2d_x)
		ft_putstr("\n");
	ft_reset_termios(g_shell.t_back);
	exit(0);
}

void 		ft_segfault(int sig)
{
	(void)sig;
	ft_putstr("Error segfault\nFin du programme\n");
	ft_reset_termios(g_shell.t_back);
	exit(0);
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

/*
 static void		ft_sigtstp(int sig)
 {
 	(void)sig;
 	if (!g_shell.running)
 	{
 		ft_reset_termios(g_shell.t_back);
 		signal(SIGTSTP, SIG_DFL);
 		ioctl(0, TIOCSTI, "\032");
 	}
 }

static void		ft_sigcont(int sig)
{
	(void)sig;
	init_termios(g_shell.my_termios);
	signal(SIGTSTP, ft_sigtstp);
}*/
void 			distrib_sig(int sig)
{
	printf("sig =%d\n", sig);
//	if (sig == SIGQUIT)
//		return ;
/*	if (sig == SIGINT)
		ft_sigint(sig);
	else if (sig == SIGWINCH)
		ft_sigwinch(sig);*/
}

void			ft_signal(void)
{
/*	FT_INIT(int, i, 1);
	while (i < 32)
	{
		signal(i, distrib_sig);
		i++;	
	}*/
	signal(SIGWINCH, ft_sigwinch);
	signal(SIGINT, ft_sigint);
	signal(SIGSEGV, ft_segfault);
//	signal(i, ft_sigkill);
//	signal(SIGTSTP, ft_sigtstp);
//	signal(SIGCONT, ft_sigcont);
}
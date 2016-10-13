/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/12 11:31:13 by jules             #+#    #+#             */
/*   Updated: 2016/10/13 10:36:02 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

// static void		ft_sigwinch(int sig)
// {
// 	t_select	*data;

// 	data = get_struct(0, 0);
// 	(void)sig;
// 	ft_clear_window();
// 	if (!check_window_size(data))
// 		ft_print(data);
// }

static void		ft_sigint(int sig)
{
	(void)sig;
	if (!g_shell.running)
	{
		ft_reset_termios(g_shell.t_back);
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, "\032");
	}
}

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
}

void			ft_signal(void)
{
	// signal(SIGWINCH, ft_sigwinch); //si on change la taille de la fenetre
	signal(SIGTSTP, ft_sigtstp);
	signal(SIGCONT, ft_sigcont);
	signal(SIGINT, ft_sigint);
}
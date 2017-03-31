/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:42 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/13 12:35:10 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

int		init_termios(struct termios my_termios)
{
	FT_INIT(char*, term_name, NULL);
	if ((term_name = get_var(g_shell.env, "TERM")) == NULL)
		term_name = ft_strdup("xterm-256color");
	if (tgetent(NULL, term_name) == ERR)
	{
		term_name = ft_strdup("xterm-256color");
		tgetent(NULL, term_name);
	}
	tcgetattr(STDIN_FILENO, &my_termios);
	my_termios.c_lflag &= ~ICANON;
	my_termios.c_lflag &= ~ECHO;
	my_termios.c_cc[VMIN] = 1;
	my_termios.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &my_termios);
	ft_strdel(&term_name);
	return (0);
}

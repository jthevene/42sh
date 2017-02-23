/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 12:21:52 by jules             #+#    #+#             */
/*   Updated: 2017/02/22 08:56:10 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int		init_termios(struct termios my_termios)
{
	FT_INIT(char*, term_name, NULL);
	FT_INIT(char*, tmp, NULL);
	FT_INIT(int, lvl_int, 0);
	if ((term_name = get_var(&g_shell, "TERM")) == NULL)
		return (1);
	if (tgetent(NULL, term_name) == ERR)
		return (1);
	tcgetattr(STDIN_FILENO, &my_termios);
	my_termios.c_lflag &= ~ICANON;
	my_termios.c_lflag &= ~ECHO;
	my_termios.c_cc[VMIN] = 1;
	my_termios.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &my_termios);
	if ((tmp = get_var(&g_shell, "SHLVL")))
	{
		ft_strdel(&term_name);
		lvl_int = ft_atoi(tmp);
		ft_strdel(&tmp);
		tmp = ft_itoa(lvl_int + 1);
		term_name = ft_strjoin("setenv SHLVL=", tmp);
		ft_setenv(term_name);
		ft_strdel(&tmp);
		ft_strdel(&term_name);
	}
	return (0);
}

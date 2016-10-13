/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 12:21:52 by jules             #+#    #+#             */
/*   Updated: 2016/10/13 13:25:45 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

int		init_termios(struct termios my_termios)
{
	char			*term_name;

	if ((term_name = getenv("TERM")) == NULL)
		return (1);
	if (tgetent(NULL, term_name) == ERR)
		return (1);
	tcgetattr(STDIN_FILENO, &my_termios);
	my_termios.c_lflag &= ~ICANON; // pour ne pas attendre un appui sur ENTER
	my_termios.c_lflag &= ~ECHO;// pour ne pas afficher les touches tapees
	my_termios.c_cc[VMIN] = 1;// pour rendre read() bloquant tant que rien n'est lu
	my_termios.c_cc[VTIME] = 0;// pour retourner immediatement quand un byte est lu
	tcsetattr(STDIN_FILENO, TCSANOW, &my_termios);
	tputs(tgetstr("ti", NULL), 1, ft_putchar_int);
	return (0);
}

void	ft_reset_termios(struct termios t_back)
{
	t_back.c_lflag |= ICANON;
	t_back.c_lflag |= ECHO;
	tcsetattr(0, 0, &t_back);
	tputs(tgetstr("te", NULL), 1, ft_putchar_int);
	tputs(tgetstr("me", NULL), 1, ft_putchar_int);
	tputs(tgetstr("vs", NULL), 1, ft_putchar_int);
}
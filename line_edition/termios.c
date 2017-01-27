/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 12:21:52 by jules             #+#    #+#             */
/*   Updated: 2016/11/07 15:31:51 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

int		init_termios(struct termios my_termios)
{
	char			*term_name;

	if ((term_name = getenv("TERM")) == NULL)
		return (1);
	if (tgetent(NULL, term_name) == ERR)
		return (1);
	tcgetattr(STDIN_FILENO, &my_termios);
	my_termios.c_lflag &= ~ICANON;
	my_termios.c_lflag &= ~ECHO;
	my_termios.c_cc[VMIN] = 1;
	my_termios.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &my_termios);
	return (0);
}

void 	free_print_line()
{
	if (g_shell.current_line)
		ft_strdel(&(g_shell.current_line));
	if (g_shell.c)
		ft_strdel(&g_shell.c);
	if (g_shell.clipboard)
		ft_strdel(&g_shell.clipboard);
}

void	ft_reset_termios(struct termios t_back)
{
	t_back.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, 0, &t_back);
	tputs(tgetstr("me", NULL), 1, ft_putchar_int);
	tputs(tgetstr("vs", NULL), 1, ft_putchar_int);
	free_print_line();
}
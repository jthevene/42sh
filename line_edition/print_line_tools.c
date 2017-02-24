/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:32:46 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void			reset_cursor_pos(void)
{
	FT_INIT(int, dif_x, g_shell.line_size - g_shell.cursor_x);
	g_shell.cursor_x = g_shell.line_size;
	while (dif_x > 0)
	{
		arrow_move_left();
		dif_x--;
	}
}

void			clean_line(void)
{
	int			i;

	i = ft_strlen(g_shell.current_line) + g_shell.prompt_len;
	g_shell.nb_rows = 1;
	if (i > g_shell.win->ws_col)
	{
		g_shell.nb_rows = i / g_shell.win->ws_col;
		if ((i % g_shell.win->ws_col) != 0)
			g_shell.nb_rows++;
	}
	tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
	tputs(tgetstr("dl", NULL), 1, ft_putchar_int);
	while (g_shell.nb_rows-- > 1)
	{
		tputs(tgetstr("dl", NULL), 1, ft_putchar_int);
		tputs(tgetstr("up", NULL), 1, ft_putchar_int);
	}
	tputs(tgetstr("cd", NULL), 1, ft_putchar_int);
}

void			go_to_end(void)
{
	FT_INIT(int, nb_col, 0);
	FT_INIT(int, test, 0);
	if (g_shell.cursor_x != g_shell.line_size &&
			g_shell.prev_cursor_2d_y > g_shell.cursor_2d_y)
		test = 1;
	nb_col = g_shell.line_size - g_shell.cursor_x;
	if (test)
		tputs(tgetstr("up", NULL), 1, ft_putchar_int);
	if (nb_col <= 0)
		return ;
	while (nb_col--)
		arrow_move_right();
}

int				set_cursor_start(int len, int ref_cursor)
{
	FT_INIT(int, go_up, g_shell.line_2d_y);
	if (go_up - g_shell.prev_line_2d_y > 1)
		go_up = g_shell.prev_line_2d_y + 1;
	if (len < g_shell.line_2d_y)
	{
		if (ref_cursor == g_shell.line_size)
			tputs(tgetstr("do", NULL), 1, ft_putchar_int);
		while (go_up-- > 0)
			tputs(tgetstr("up", NULL), 1, ft_putchar_int);
		len = g_shell.line_2d_y;
	}
	else
		tputs(tgetstr("rc", NULL), 1, ft_putchar_int);
	tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
	tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_int);
	ft_putstr(g_shell.prompt);
	return (len);
}

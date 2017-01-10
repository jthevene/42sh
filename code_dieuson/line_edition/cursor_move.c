/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:38:47 by jules             #+#    #+#             */
/*   Updated: 2016/11/08 16:12:16 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

int		ft_cursor_right(int i)
{
	FT_INIT(int, len, g_shell.line_size);
	if (i < 0 || g_shell.cursor_x > len)
		return (0);
	while (i > 0 && g_shell.cursor_x <= len)
	{
		tputs(tgetstr("nd", NULL), 1, ft_putchar_int);
		i--;
	}
	return (1);
}

void 	arrow_moove_left()
{
	FT_INIT(int, len, g_shell.line_size);
	FT_INIT(int, cursor_x, g_shell.cursor_x);
	set_2d_line_val();
	set_2d_cursor_val();
	if (cursor_x - 1 <= len && cursor_x - 1 >= 3)
	{
		if (g_shell.cursor_2d_x && g_shell.cursor_x > 3)
			tputs(tgetstr("le", NULL), 1, ft_putchar_int);
		else
		{
			tputs(tgetstr("up", NULL), 1, ft_putchar_int);
			tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
			ft_cursor_right(g_shell.win->ws_col);
		}
		cursor_x--;
		g_shell.cursor_x = cursor_x;
	}
	set_2d_cursor_val();
}

void 	arrow_moove_right()
{
	FT_INIT(int, len, g_shell.line_size);
	FT_INIT(int, cursor_x, g_shell.cursor_x);
	set_2d_line_val();
	set_2d_cursor_val();
	if (cursor_x < len && cursor_x >= 3)
	{
		if (g_shell.cursor_2d_x + 1 < g_shell.win->ws_col 
		&& g_shell.cursor_x <= len)
			tputs(tgetstr("nd", NULL), 1, ft_putchar_int);
		else
			ft_putstr("\n");
		cursor_x++;
		g_shell.cursor_x = cursor_x;
	}
	set_2d_cursor_val();
}

void 	moove_one_word(int direction)
{
	void (*function)(void);

	function = direction > 0 ? arrow_moove_right : arrow_moove_left;
	FT_INIT(char *, line, g_shell.current_line);
	FT_INIT(int, i, g_shell.cursor_x - 3);
	if (!line || i < 0)
		return ;
	if (line[i] != ' ' && direction < 0)
		function();
	i = line[i] != ' ' && direction < 0 ? i + direction : i;
	while (line && i >= 0 && line[i] && line[i] == ' ')
	{
		function();
		i += direction;
	}
	while (line && i >= 0 && line[i] && line[i] != ' ')
	{
		function();
		i += direction;
	}
	if (line[i] == ' ' && direction < 0)
		arrow_moove_right();
}

int 	distrib_cursor_mooves(int key)
{
	FT_INIT(int, nb_col, g_shell.win->ws_col);
	if (key == K_UP || key == K_DOWN)
	{
		go_to_end();
		navigation_hist(key);
	}
	else if (key == K_RIGHT)
		arrow_moove_right();
	else if (key == K_LEFT)
		arrow_moove_left();
	else if (key == K_OW_RIGHT)
		moove_one_word(1);
	else if (key == K_OW_LEFT)
		moove_one_word(-1);
	else if (key == K_OL_UP && g_shell.line_2d_y && g_shell.cursor_2d_y)
	{
		while (nb_col--)
			arrow_moove_left();
	}
	else if (key == K_OL_DOWN && g_shell.cursor_2d_y < g_shell.line_2d_y)
	{
		while (nb_col--)
			arrow_moove_right();
	}
	else if (key == K_GO_END)
	{
		nb_col = g_shell.line_size - g_shell.cursor_x;
		while (nb_col--)
			arrow_moove_right();
	}
	else if (key == K_GO_START)
	{
		nb_col = g_shell.cursor_x;
		while (nb_col--)
			arrow_moove_left();
	}
	else
		return (0);
	return (0);
}
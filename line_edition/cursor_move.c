/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:42 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:45:46 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

void			arrow_move_right(void)
{
	FT_INIT(int, len, g_shell.line_size);
	FT_INIT(int, cursor_x, g_shell.cursor_x);
	set_2d_edition_val();
	if (cursor_x < len && cursor_x >= g_shell.prompt_len)
	{
		if (g_shell.cursor_2d_x + 1 < g_shell.win->ws_col
		&& g_shell.cursor_x <= len)
			tputs(tgetstr("nd", NULL), 1, ft_putchar_int);
		else
			ft_putstr("\n");
		cursor_x++;
		g_shell.cursor_x = cursor_x;
	}
	set_2d_edition_val();
}

void			arrow_move_left(void)
{
	FT_INIT(int, len, g_shell.line_size);
	FT_INIT(int, cursor_x, g_shell.cursor_x);
	set_2d_edition_val();
	if (cursor_x - 1 <= len && cursor_x - 1 >= g_shell.prompt_len)
	{
		if (g_shell.cursor_2d_x && g_shell.cursor_x > g_shell.prompt_len)
			tputs(tgetstr("le", NULL), 1, ft_putchar_int);
		else
		{
			tputs(tgetstr("up", NULL), 1, ft_putchar_int);
			tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
			FT_INIT(int, nb_col, g_shell.win->ws_col);
			while (nb_col-- > 0)
				tputs(tgetstr("nd", NULL), 1, ft_putchar_int);
		}
		cursor_x--;
		g_shell.cursor_x = cursor_x;
	}
	set_2d_edition_val();
}

void			move_one_word(int direction)
{
	void (*function)(void);

	function = direction > 0 ? arrow_move_right : arrow_move_left;
	FT_INIT(char *, line, g_shell.current_line);
	FT_INIT(int, i, g_shell.cursor_x - g_shell.prompt_len);
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
		arrow_move_right();
}

void			move_cursor_n_to_direction(int n, int direction)
{
	void (*function)(void);

	function = direction > 0 ? arrow_move_right : arrow_move_left;
	while (n > 0)
	{
		function();
		n--;
	}
}

int				distrib_cursor_moves(int key)
{
	if (key == K_UP || key == K_DOWN)
	{
		go_to_end();
		navigation_hist(key);
	}
	else if (key == K_RIGHT)
		arrow_move_right();
	else if (key == K_LEFT)
		arrow_move_left();
	else if (key == K_OW_RIGHT)
		move_one_word(1);
	else if (key == K_OW_LEFT)
		move_one_word(-1);
	else if (key == K_OL_UP && g_shell.line_2d_y && g_shell.cursor_2d_y)
		move_cursor_n_to_direction(g_shell.win->ws_col, -1);
	else if (key == K_OL_DOWN && g_shell.cursor_2d_y < g_shell.line_2d_y)
		move_cursor_n_to_direction(g_shell.win->ws_col, 1);
	else if (key == K_GO_END)
		move_cursor_n_to_direction((g_shell.line_size - g_shell.cursor_x), 1);
	else if (key == K_GO_START)
		move_cursor_n_to_direction(g_shell.cursor_x, -1);
	else
		return (0);
	return (0);
}

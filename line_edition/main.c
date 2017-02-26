/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:32:48 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void			display_prompt(void)
{
	g_shell.prompt = set_prompt(get_var(&g_shell, "PWD"));
	ft_putstr(g_shell.prompt);
	tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
}

void			set_2d_edition_val(void)
{
	FT_INIT(int, ref_x, ft_strlen(g_shell.current_line) + g_shell.prompt_len);
	FT_INIT(int, y, 0);
	g_shell.line_size = ref_x;
	while (ref_x >= g_shell.win->ws_col)
	{
		y++;
		ref_x -= g_shell.win->ws_col;
	}
	g_shell.line_2d_y = y;
	g_shell.line_2d_x = ref_x;
	ref_x = g_shell.cursor_x;
	y = 0;
	while (ref_x >= g_shell.win->ws_col)
	{
		y++;
		ref_x -= g_shell.win->ws_col;
	}
	if (ref_x == g_shell.win->ws_col)
	{
		y++;
		ref_x = 0;
	}
	g_shell.cursor_2d_y = y;
	g_shell.cursor_2d_x = ref_x;
}

static void		parse_capabilities(int key)
{
	if (distrib_cursor_moves(key))
		;
	else if (key == K_BACKSP || key == K_DEL)
		backspace_key(key);
	else if (key == K_COPY || key == K_CUT)
		copy_cut_line(key);
	else if (key == K_RETURN)
	{
		return_key();
		g_shell.cursor_x = g_shell.prompt_len;
		set_2d_edition_val();
	}
	else if (key == K_TAB)
	{
		detect_auto_completion(g_shell.current_line);
		print_line(1);
	}
	else if (key == K_ESCAPE)
		ft_sigkill(SIGINT);
}

static void		run_shell(void)
{
	FT_INIT(int, key, 0);
	g_shell.cursor_x = g_shell.prompt_len;
	ioctl(0, TIOCGWINSZ, g_shell.win);
	while (42)
	{
		key = readkey();
		if (key == K_PRINT)
		{
			MULTI(g_shell.start_select, g_shell.end_select, 0);
			g_shell.prompt = set_prompt(get_var(&g_shell, "PWD"));
			fill_current_line(g_shell.c[0]);
			g_shell.cursor_x++;
			print_line(1);
		}
		else
			parse_capabilities(key);
	}
}

int				main(void)
{
	if (init_all())
		return (0);
	display_prompt();
	run_shell();
	return (0);
}

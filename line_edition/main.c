/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:42 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/23 18:55:08 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

void			display_prompt(void)
{
	g_shell.prompt = set_prompt(getcwd(NULL, 1024));
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

void			parse_capabilities(int key)
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
		detect_auto_completion(g_shell.current_line, true);
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
			g_shell.prompt = set_prompt(getcwd(NULL, 1024));
			fill_current_line(g_shell.c[0]);
			g_shell.cursor_x++;
			print_line(1);
		}
		else
			parse_capabilities(key);
	}
}

int				main(int ac, char **av, char **envp)
{
	if (!ac || !av || init_all(envp))
		return (0);
	display_prompt();
	run_shell();
	return (0);
}

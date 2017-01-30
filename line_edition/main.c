/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:20:49 by jules             #+#    #+#             */
/*   Updated: 2016/12/08 14:49:56 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

void		display_prompt(void)
{
	g_shell.prompt = set_prompt(get_var(&g_shell, "PWD"));
	ft_putstr(g_shell.prompt);
	tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
}

void 		set_2d_line_val()
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
}

void 		set_2d_cursor_val()
{
	FT_INIT(int, ref_x, g_shell.cursor_x);
	FT_INIT(int, y, 0);
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

static	void	run_shell(void)
{
	int 	key;
	int 	i;

	i = 0;
	g_shell.cursor_x = g_shell.prompt_len;
	ioctl(0, TIOCGWINSZ, g_shell.win);
	while (42)
	{
		g_shell.running = 1;
		key = readkey();
		if (key == K_PRINT)
		{
			MULTI(g_shell.start_select, g_shell.end_select, 0);
			fill_current_line(g_shell.c[0]);
			g_shell.cursor_x++;
			print_line(i);
			i++;

		}
		else if (distrib_cursor_mooves(key))
			;
		else if (key == K_BACKSP || key == K_DEL)
		{
			backspace_key(key);
			i = ft_strlen(g_shell.current_line);
		}
		else if (key == K_COPY || key == K_CUT)
		{
			copy_cut_line(key);
			i = ft_strlen(g_shell.current_line);			
		}
		else if (key == K_RETURN)
		{
			return_key();
			i = 0;
			g_shell.cursor_x = g_shell.prompt_len;
			set_2d_line_val();
			set_2d_cursor_val();
		}
		else if (key == K_ESCAPE)
			return (ft_exit());
		else if (key == K_TAB)
		{
			detect_auto_completion(g_shell.current_line);
			print_line(i);
		}
		g_shell.running = 0;
	}
}

int		main(void)
{
	if (init_all())
		return (0);
	display_prompt();
	run_shell();
	return (0);
}
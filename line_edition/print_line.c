/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 10:41:51 by jules             #+#    #+#             */
/*   Updated: 2016/11/08 17:23:08 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

void 	reset_cursor_pos()
{
	FT_INIT(int, dif_x, g_shell.line_size - g_shell.cursor_x);
	g_shell.cursor_x = g_shell.line_size;
	while (dif_x > 0)
	{
	 	arrow_move_left();
		dif_x--;
	}
}

void 	display_with_select(char *line)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, start_select, - g_shell.prompt_len);
	FT_INIT(int, end_select, - g_shell.prompt_len);
	if (!g_shell.start_select || !g_shell.end_select)
		return ;
	start_select += g_shell.start_select < g_shell.end_select ? 
					g_shell.start_select : g_shell.end_select;
	end_select += g_shell.end_select > g_shell.start_select ? 
					g_shell.end_select : g_shell.start_select;
	while (line[i])
	{
		if (i == start_select)
			ft_putstr("\033[47m\033[30m");
		ft_putchar(line[i]);
		if (i == end_select || (i == end_select - 1 
			&& end_select == g_shell.line_size - g_shell.prompt_len))
			ft_putstr("\033[0m\033[0m");
		i++;
	}
}

void	clean_line()
{
	int i;
	
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
}

void 	go_to_end()
{
	FT_INIT(int, nb_col, 0);
	nb_col = g_shell.line_size - g_shell.cursor_x;
	if (nb_col <= 0)
		return ;
	while (nb_col--)
		arrow_move_right();
}

int 	set_cursor_start(int len, int ref_cursor)
{
	FT_INIT(int, go_up, g_shell.line_2d_y);
	if (go_up - g_shell.prev_line_2d_y > 1)
		go_up = g_shell.prev_line_2d_y + 1;
	if (len < g_shell.line_2d_y)
	{
		if (ref_cursor == g_shell.line_size)
			tputs(tgetstr("do", NULL), 1, ft_putchar_int);
		while (go_up-- > 0)
			tputs(tgetstr("up", NULL), 1, ft_putchar_int); // scroll up
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

char 	*set_prompt(char *pwd)
{
	FT_INIT(char*, head_line, ft_strdup("\033[32m$> \033[0m"));
	FT_INIT(char*, tmp, NULL);
	FT_INIT(char*, home, get_var(&g_shell, "HOME"));
	g_shell.prompt_len = 3;
	if (!pwd)
		return (head_line);
	if (!ft_strncmp(pwd, home, ft_strlen(home)))
	{
		tmp = pwd;
		pwd = ft_str_replace(pwd, home, "~");
		if (pwd)
			ft_strdel(&tmp);
		else
			pwd = tmp;
	}
	tmp = head_line;
	head_line = ft_strjoin(pwd, head_line);
	ft_strdel(&tmp);
	g_shell.prompt_len += ft_strlen(pwd);
	if (g_shell.prompt)
		ft_strdel(&g_shell.prompt);
	return (head_line);
}

void	print_line(int i)
{
	g_shell.prompt = set_prompt(get_var(&g_shell, "PWD"));
	set_2d_edition_val();
	FT_INIT(int, ref_cursor, g_shell.cursor_x);
	if (i)
		i--;
	go_to_end();
	g_shell.len = set_cursor_start(g_shell.len, ref_cursor);
	if (!g_shell.start_select && !g_shell.end_select)
		ft_putstr(g_shell.current_line);
	else
		display_with_select(g_shell.current_line);
	if (!g_shell.line_2d_x && g_shell.cursor_x == g_shell.line_size)	
		ft_putstr("\n");
	g_shell.cursor_x = ref_cursor;
	reset_cursor_pos();
	g_shell.prev_line_2d_y = g_shell.line_2d_y;
	return ;
}
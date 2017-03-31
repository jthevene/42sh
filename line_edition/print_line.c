/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:42 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/13 12:35:17 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

static void			display_with_select(char *line)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, start_select, -g_shell.prompt_len);
	FT_INIT(int, end_select, -g_shell.prompt_len);
	if (!g_shell.start_select || !g_shell.end_select)
		return ;
	start_select += g_shell.start_select < g_shell.end_select ?
					g_shell.start_select : g_shell.end_select;
	end_select += g_shell.end_select > g_shell.start_select ?
					g_shell.end_select : g_shell.start_select;
	while (line && line[i])
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

static void			free_them(char **s1, char **s2, char **s3)
{
	ft_strdel(s1);
	ft_strdel(s2);
	ft_strdel(s3);
	if (g_shell.prompt)
		ft_strdel(&g_shell.prompt);
}

char				*set_prompt(char *pwd)
{
	FT_INIT(char*, head_line, ft_strdup("\033[32m$> \033[0m"));
	FT_INIT(char*, tmp, NULL);
	FT_INIT(char*, home, get_var(g_shell.env, "HOME"));
	pwd = pwd ? pwd : ft_strdup(g_shell.line);
	g_shell.prompt_len = 3;
	if (!pwd)
	{
		if (g_shell.prompt)
			ft_strdel(&g_shell.prompt);
		if (home)
			ft_strdel(&home);
		return (head_line);
	}
	if (home && !ft_strncmp(pwd, home, ft_strlen(home)))
	{
		tmp = pwd;
		pwd = ft_str_replace(pwd, home, "~");
		ft_strdel(pwd ? &tmp : NULL);
		pwd = !pwd ? tmp : pwd;
	}
	tmp = head_line;
	head_line = ft_strjoin(pwd, head_line);
	g_shell.prompt_len += ft_strlen(pwd);
	free_them(&tmp, &home, &pwd);
	return (head_line);
}

void				print_line(int i)
{
	set_2d_edition_val();
	FT_INIT(int, ref_cursor, g_shell.cursor_x);
	(void)i;
	if (!g_shell.current_line)
		return ;
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
	g_shell.prev_cursor_2d_y = g_shell.cursor_2d_y;
	return ;
}

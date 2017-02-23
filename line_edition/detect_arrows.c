/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_arrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 17:59:34 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/22 08:56:17 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

static int		detect_selection_text(char *key, int start,
		int end, int cursor_x)
{
	if (key[4] == 50 && key[5] == 68)
	{
		g_shell.start_select = start ? start : cursor_x - 1;
		if (end && end < cursor_x)
			g_shell.end_select = cursor_x;
		if (end && end < cursor_x && cursor_x == start + 1)
			g_shell.end_select = g_shell.end_select > g_shell.prompt_len ?
				g_shell.end_select - 1 : g_shell.end_select;
		else if (end && end < cursor_x)
			g_shell.end_select = g_shell.end_select > g_shell.prompt_len ?
				g_shell.end_select - 2 : g_shell.end_select;
		if (!(end && end < cursor_x))
			g_shell.end_select = cursor_x > g_shell.prompt_len ?
				cursor_x - 1 : cursor_x;
		print_line(g_shell.line_size);
		return (K_LEFT);
	}
	return (0);
}

static int		arrow_combo(char *key)
{
	FT_INIT(int, start, g_shell.start_select);
	FT_INIT(int, end, g_shell.end_select);
	if (key[0] == 27 && key[1] == 27 && key[2] == 91 && key[3] == 67)
		return (K_OW_RIGHT);
	else if (key[0] == 27 && key[1] == 27 && key[2] == 91 && key[3] == 68)
		return (K_OW_LEFT);
	else if (key[0] == 27 && key[1] == 27 && key[2] == 91 && key[3] == 65)
		return (K_OL_UP);
	else if (key[0] == 27 && key[1] == 27 && key[2] == 91 && key[3] == 66)
		return (K_OL_DOWN);
	else if (key[4] == 50 && key[5] == 67)
	{
		g_shell.start_select = start ? start : g_shell.cursor_x;
		g_shell.end_select = (end && end == g_shell.cursor_x ?
			g_shell.cursor_x + 1 : g_shell.cursor_x);
		if (g_shell.end_select >= g_shell.line_size)
			g_shell.end_select = g_shell.line_size - 1;
		print_line(g_shell.line_size);
		return (K_RIGHT);
	}
	else
		return (detect_selection_text(key, start, end, g_shell.cursor_x));
}

int				detect_arrow(char *key)
{
	if (g_shell.start_select && g_shell.end_select && !(key[4] == 50
		&& (key[5] == 67 || key[5] == 68 || key[5] == 65 || key[5] == 66)))
	{
		MULTI(g_shell.start_select, g_shell.end_select, 0);
		print_line(g_shell.line_size);
	}
	if (key[0] == 27 && key[1] == 91 && key[2] == 67)
		return (K_RIGHT);
	else if (key[0] == 27 && key[1] == 91 && key[2] == 68)
		return (K_LEFT);
	else if (key[0] == 27 && key[1] == 91 && key[2] == 65)
		return (K_UP);
	else if (key[0] == 27 && key[1] == 91 && key[2] == 66)
		return (K_DOWN);
	return (arrow_combo(key));
}

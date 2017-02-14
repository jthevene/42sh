/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_arrows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 17:59:34 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/13 12:37:36 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static int				detect_selection_text(char *key, int start,
												int end, int cursor_x)
{
	// Selection zone de text SHIFT + LEFT
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

static int				arrow_combo(char *key)
{
	FT_INIT(int, start, g_shell.start_select);
	FT_INIT(int, end, g_shell.end_select);
	if (key[2] != 49 || key[3] != 59)
		return (0);
	if (key[4] == 53 && key[5] == 67)
		return (K_OW_RIGHT); // OW -> ONE WORD
	else if (key[4] == 53 && key[5] == 68)
		return (K_OW_LEFT);
	else if (key[4] == 53 && key[5] == 65)
		return (K_OL_UP); 	// OL -> ONE LINE
	else if (key[4] == 53 && key[5] == 66)
		return (K_OL_DOWN);
	else if (key[4] == 50 && key[5] == 67)// Selection zone de text SHIFT + RIGHT
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

int						detect_arrow(char *key)
{
	if (g_shell.start_select && g_shell.end_select && !(key[4] == 50
		&& (key[5] == 67 || key[5] == 68 || key[5] == 65 || key[5] == 66)))
	{
		ft_printf("\nTEST\n");
		MULTI(g_shell.start_select, g_shell.end_select, 0);// On remet a zero la zone de selection
		print_line(g_shell.line_size);
	}
	if (key[0] != 27 || key[1] != 91)
		return (0);
	if (key[2] == 67 && key[3] == 0)
		return (K_RIGHT);
	else if (key[2] == 68 && key[3] == 0)
		return (K_LEFT);
	else if (key[2] == 65 && key[3] == 0)
		return (K_UP);
	else if (key[2] == 66 && key[3] == 0)
		return (K_DOWN);
	return (arrow_combo(key));
}
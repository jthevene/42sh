/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_cut_past.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:42 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:45:46 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

static char		*store_selection(int start_select, int end_select, int key)
{
	FT_INIT(char*, clipboard, NULL);
	FT_INIT(int, nb_del, 0);
	FT_INIT(int, len_current_line, (int)ft_strlen(g_shell.current_line));
	if (end_select > len_current_line)
		end_select = len_current_line;
	clipboard = ft_strsub(g_shell.current_line, start_select,
		ft_abs(end_select - start_select));
	if (key == K_CUT)
	{
		nb_del = end_select - start_select;
		end_select = nb_del;
		while (g_shell.cursor_x > g_shell.start_select && nb_del--)
			arrow_move_left();
		nb_del = end_select;
		g_shell.cursor_x++;
		while (nb_del--)
			backspace_key(0);
		g_shell.cursor_x--;
	}
	MULTI(g_shell.start_select, g_shell.end_select, 0);
	print_line(g_shell.line_size);
	if (g_shell.clipboard)
		ft_strdel(&g_shell.clipboard);
	return (clipboard);
}

void			copy_cut_line(int key)
{
	FT_INIT(int, start_select, -g_shell.prompt_len);
	FT_INIT(int, end_select, -g_shell.prompt_len);
	if (!g_shell.start_select || !g_shell.end_select)
		return ;
	start_select += g_shell.start_select < g_shell.end_select ?
		g_shell.start_select : g_shell.end_select;
	end_select += g_shell.end_select > g_shell.start_select ?
		g_shell.end_select : g_shell.start_select;
	end_select++;
	if (end_select - start_select <= 0 || start_select < 0 || end_select < 0)
		return ;
	g_shell.clipboard = store_selection(start_select, end_select, key);
}

void			past_line(char *clipboard)
{
	FT_INIT(int, i, 0);
	if (!clipboard)
		return ;
	while (clipboard[i])
	{
		fill_current_line(clipboard[i]);
		g_shell.cursor_x++;
		i++;
	}
	print_line(g_shell.line_size);
}

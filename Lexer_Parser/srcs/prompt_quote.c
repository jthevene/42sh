/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <dvirgile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:41 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/10 16:52:29 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static void		modif_prompt(char *modif_by)
{
	if (g_shell.prompt)
		ft_strdel(&g_shell.prompt);
	g_shell.prompt = ft_strdup(modif_by);
	g_shell.prompt_len = ft_strlen(g_shell.prompt);
}

static int		detect_input_type(int key)
{
	if (key == K_DEL || key == K_DEL)
		backspace_key(K_DEL);
	else if (key == K_BACKSP)
		backspace_key(K_BACKSP);
	else if (key == K_RIGHT || key == K_LEFT || key == K_OW_RIGHT ||
		key == K_OW_LEFT || key == K_OL_UP || key == K_OL_DOWN ||
		key == K_GO_END || key == K_GO_START)
		distrib_cursor_moves(key);
	else if (key == K_PRINT)
		return (1);
	else if (key == K_COPY || key == K_CUT)
		copy_cut_line(key);
	else if (key == K_TAB)
	{
		detect_auto_completion(g_shell.current_line, false);
		print_line(1);
	}
	return (0);
}

char			*prompt_dquote(char *quote_type)
{
	FT_INIT(int, key, 0);
	g_shell.cursor_x = ft_strlen(quote_type);
	tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
	modif_prompt(quote_type);
	ft_bzero(g_shell.c, 16);
	ft_bzero(g_shell.current_line, ft_strlen(g_shell.current_line));
	print_line(1);
	g_shell.running = 2;
	while ((key = readkey()))
	{
		g_shell.running = 2;
		if (g_shell.c[0] == 10)
			break ;
		else if (key == K_ESCAPE && !((int)ft_strlen(g_shell.current_line)))
			return (NULL);
		else if (detect_input_type(key) == K_PRINT)
		{
			fill_current_line(g_shell.c[0]);
			g_shell.cursor_x++;
		}
		print_line(1);
	}
	return (g_shell.current_line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 09:11:45 by jules             #+#    #+#             */
/*   Updated: 2017/02/21 13:25:31 by jthevene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

void	reset_line(void)
{
	free(g_shell.line);
	move_cursor_n_to_direction(g_shell.line_size, 1);
	if (g_shell.cursor_2d_x)
		ft_putchar('\n');
	if (g_shell.current_line)
		ft_strdel(&g_shell.current_line);
	g_shell.current_line = NULL;
	g_shell.nav_hist = 0;
	free_hist_opt();
	init_hist_opt();
}

void	return_key(void)
{
	go_to_end();
	FT_INIT(int, add_hist, 0);
	if (ft_strlen(g_shell.current_line))
	{
		if (g_shell.current_line && ft_strchr(g_shell.current_line, '!'))
			add_hist += history_event(g_shell.current_line);
		ft_putchar(10);
		g_shell.result_exec = -99;
		g_shell.all_results = -99;
		lexer_parser(ft_strdup(g_shell.current_line));
		reset_line();
	}
	else
		ft_putchar(10);
	g_shell.curr_hist = g_shell.hist;
	g_shell.len = 0;
	display_prompt();
}

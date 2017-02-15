/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation_hist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/14 12:38:56 by jules             #+#    #+#             */
/*   Updated: 2017/02/14 13:10:43 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

void	navigation_hist(int arrow)
{
	if (g_shell.curr_hist)
	{
		if (arrow == K_UP)
			nav_hist_up();
		else
			nav_hist_down();
	}
}

static void 	replace_current_line(char *content)
{
	FT_INIT(int, i, 0);
	if (!content)
		return ;
	g_shell.cursor_x = g_shell.prompt_len;
	if (g_shell.current_line)
		ft_strdel(&g_shell.current_line);
	while (content && content[i])
	{
		fill_current_line(content[i]);
		g_shell.cursor_x++;
		i++;
	}
	g_shell.line_size = g_shell.cursor_x;

}

void	nav_hist_up(void)
{
	if (g_shell.curr_hist->prev && g_shell.curr_hist->prev->content)
	{
		if (g_shell.nav_hist == 1)
			g_shell.curr_hist = g_shell.curr_hist->prev;
		g_shell.nav_hist = 1;
		put_hist_line(g_shell.curr_hist->content);
		replace_current_line(g_shell.curr_hist->content);
	}
}

void	nav_hist_down(void)
{
	if (g_shell.curr_hist->next)
	{
		g_shell.curr_hist = g_shell.curr_hist->next;
		put_hist_line(g_shell.curr_hist->content);
		replace_current_line(g_shell.curr_hist->content);
	}
}

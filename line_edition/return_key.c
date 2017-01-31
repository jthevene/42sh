/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 13:12:22 by jules             #+#    #+#             */
/*   Updated: 2017/01/28 14:43:40 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

static void 	reset_line(void)
{
	free(g_shell.line);
	move_cursor_n_to_direction(g_shell.line_size, 1);
	if (g_shell.cursor_2d_x)
		ft_putchar('\n');
	if (g_shell.current_line && !g_shell.hist_opt.p) //on ajoute la ligne à l'historique seulement si la ligne est non nulle && si pas history -p
		ft_newhist(g_shell.current_line);
	else
		g_shell.hist->content = ft_strdup(g_shell.current_line);
		g_shell.hist->number++;
	g_shell.current_line = NULL;
	g_shell.nav_hist = 0;
	ft_bzero(g_shell.current_line, ft_strlen(g_shell.current_line));

}

void	return_key(void)
{ 
	go_to_end();
	if (ft_strlen(g_shell.current_line))
	{
		lexer_parser(g_shell.current_line);
		ft_putchar(10);
		g_shell.line = ft_strdup(g_shell.current_line);
		reset_line();
	}
	else
		ft_putchar(10);
	g_shell.curr_hist = g_shell.hist;
	g_shell.len = 0;
	display_prompt();
}
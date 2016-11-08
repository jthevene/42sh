/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 10:41:51 by jules             #+#    #+#             */
/*   Updated: 2016/11/07 15:03:07 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

// efface la ligne en cours d'edition
void	clean_line()
{
//	int i;
	int nb_rows;
	
//	i = ft_strlen(g_shell.current_line) + 2;
	nb_rows = g_shell.cursor_y + 1;
	tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
	tputs(tgetstr("dl", NULL), 1, ft_putchar_int);
	while (nb_rows-- > 1)
	{
		tputs(tgetstr("dl", NULL), 1, ft_putchar_int);
		tputs(tgetstr("up", NULL), 1, ft_putchar_int);
	}
	// while (g_shell.cursor_y-- >= 0)
	// {
	// 	tputs(tgetstr("dl", NULL), 1, ft_putchar_int);
	// 	tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
	// 	if (g_shell.cursor_y > 0)
	// 		tputs(tgetstr("up", NULL), 1, ft_putchar_int);
	// }
}

void	print_line(int i)
{
	int 	j;

	j = 0;
	clean_line();
	g_shell.cursor_x = 0;
	g_shell.cursor_y = 0;
	display_prompt();
	tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
	while (j < i + 1)
	{
		ft_putchar(g_shell.current_line[j]);
		g_shell.cursor_x++;
		j++;
		if (g_shell.cursor_x == g_shell.win->ws_col)
		{
			cursor_next_line();
			g_shell.cursor_x = 0;
			g_shell.cursor_y++;
		}
	}
}
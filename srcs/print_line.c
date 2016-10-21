/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 10:41:51 by jules             #+#    #+#             */
/*   Updated: 2016/10/21 12:36:43 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	clean_line(int i)
{
	int 	nb_rows;

	i += 3;
	nb_rows = 1;
	if (i > g_shell.win->ws_col)
		nb_rows = i / g_shell.win->ws_col;
	while (nb_rows > 0)
	{
		i = g_shell.win->ws_col;
		// tputs(tgetstr("dl", NULL), 1, ft_putchar_int);
		while (i-- > 0)
			tputs(tgetstr("le", NULL), 1, ft_putchar_int);
		if (nb_rows > 1)
		{
			ft_putchar('O');
			tputs(tgetstr("up", NULL), 1, ft_putchar_int);
		}
		nb_rows--;
	}
}

void	print_line(int i)
{
	int 	j;

	j = 0;
	clean_line(i); // i = nb de char déjà écris et que l'on va effacer
	display_prompt();
	while (j < i + 1)
	{
		if (j + 3 == g_shell.win->ws_col)
		{
			cursor_next_line();
		}
		ft_putchar(g_shell.current_line[j]);
		j++;
	}
}
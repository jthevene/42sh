/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/14 10:41:51 by jules             #+#    #+#             */
/*   Updated: 2016/11/03 11:58:32 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

// efface la ligne en cours d'edition
void	clean_line()
{
	int 	i;
	int 	nb_rows;

	i = ft_strlen(g_shell.current_line) + 2;
	nb_rows = 1;
	if (i > g_shell.win->ws_col)
	{
		nb_rows = i / g_shell.win->ws_col;
		if ((i % g_shell.win->ws_col) != 0)
			nb_rows++;
	}
	while (nb_rows > 0)
	{
		i = g_shell.win->ws_col;
		tputs(tgetstr("dl", NULL), 1, ft_putchar_int);
		while (i-- > 0)
			tputs(tgetstr("le", NULL), 1, ft_putchar_int);
		if (nb_rows > 1)
			tputs(tgetstr("up", NULL), 1, ft_putchar_int);
		nb_rows--;
	}
}

void	print_line(int i)
{
	int 	j;

	j = 0;
	(void)i;
	clean_line();
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
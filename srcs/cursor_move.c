/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:38:47 by jules             #+#    #+#             */
/*   Updated: 2016/10/18 15:11:09 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		ft_cursor_right(int i)
{
	while (i-- > 0)
		tputs(tgetstr("nd", NULL), 1, ft_putchar_int);
}

void		ft_cursor_left(int i)
{
	while (i-- > 0)
		tputs(tgetstr("le", NULL), 1, ft_putchar_int);
}

void		cursor_next_line(void)
{
	int 	i;

	if (g_shell.current_line)
	{
		i = ft_strlen(g_shell.current_line);
		while (i-- > 0)
			tputs(tgetstr("le", NULL), 1, ft_putchar_int);
	}
	else
	{
		i = 3;
		while (i-- > 0)
			tputs(tgetstr("le", NULL), 1, ft_putchar_int);
	}
	tputs(tgetstr("do", NULL), 1, ft_putchar_int);
}
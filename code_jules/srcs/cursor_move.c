/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/13 14:38:47 by jules             #+#    #+#             */
/*   Updated: 2016/11/08 16:12:16 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

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

// recule le curseur vers la gauche et descend d'une ligne
void		cursor_next_line(void)
{
	// int 	i;

	// if (g_shell.current_line)
	// {
	// 	i = ft_strlen(g_shell.current_line);
	// 	while (i-- > 0)
	// 		tputs(tgetstr("le", NULL), 1, ft_putchar_int);
	// }
	// else
	// {
	// 	i = 3;
	// 	while (i-- > 0)
	// 		tputs(tgetstr("le", NULL), 1, ft_putchar_int);
	// }
	tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
	tputs(tgetstr("do", NULL), 1, ft_putchar_int);
}
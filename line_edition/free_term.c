/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 17:38:34 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/22 08:56:16 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

static void			free_edition_line(void)
{
	free(g_shell.current_line);
	free(g_shell.c);
	free(g_shell.clipboard);
	free(g_shell.oldpwd);
	free(g_shell.prompt);
	free(g_shell.win);
}

void				ft_reset_termios(struct termios t_back)
{
	t_back.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, 0, &t_back);
	tputs(tgetstr("me", NULL), 1, ft_putchar_int);
	tputs(tgetstr("vs", NULL), 1, ft_putchar_int);
	free_edition_line();
}

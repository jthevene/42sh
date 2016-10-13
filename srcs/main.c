/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:20:49 by jules             #+#    #+#             */
/*   Updated: 2016/10/13 17:05:19 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

extern t_shell		g_shell;

static void		display_prompt(void)
{
	ft_putstr("\033[32m$> \033[0m");
}

static	void	run_shell(void)
{
	int 	key;

	while (42)
	{
		g_shell.running = 1;
		display_prompt();
		key = readkey();
		// if (key == K_RETURN)
		// 	handle_line();
		// if (key == K_PRINT)
		// else if (key == K_UP || key == K_DOWN)
		// else if (key == K_RIGHT || key == K_LEFT)
		// else if (key == K_SPACE)
		// else if (key == K_DEL)
		// else if (key == K_ESCAPE)
		g_shell.running = 0;
	}
}

int		main(void)
{
	if (init_all())
		return (0);
	ft_putstr("init_all DONE/n");
	ft_reset_termios(g_shell.t_back);
	run_shell();
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:20:49 by jules             #+#    #+#             */
/*   Updated: 2016/10/20 12:12:07 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		display_prompt(void)
{
	ft_putstr("\033[32m$> \033[0m");
	g_shell.cursor_x += 2;
}

static	void	run_shell(void)
{
	int 	key;
	int 	i;

	i = 0;
	while (42)
	{
		g_shell.running = 1;
		key = readkey();
		if (key == K_PRINT)
		{
			g_shell.cursor_x += 1;	
			print_line(i++);
		}
		else if (key == K_UP || key == K_DOWN)
			ft_putendl("UP/DOWN");
		else if (key == K_RIGHT || key == K_LEFT)
			ft_putendl("RIGHT/LEFT");
		else if (key == K_BACKSP)
			backspace_key();
		else if (key == K_RETURN)
		{
			return_key();
			i = 0;
		}
		else if (key == K_ESCAPE)
		{
			ft_reset_termios(g_shell.t_back);
			return;
		}
		g_shell.running = 0;
	}
}

int		main(void)
{
	if (init_all())
		return (0);
	display_prompt();
	run_shell();
	return (0);
}
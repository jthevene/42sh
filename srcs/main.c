/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:20:49 by jules             #+#    #+#             */
/*   Updated: 2016/10/18 10:53:41 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static void		display_prompt(void)
{
	ft_putstr("\033[32m$> \033[0m");
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
		// clean_line();
		// tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putchar_int);
		// if (key == K_RETURN)
		// 	handle_line();
		if (key == K_PRINT)
		{
			clean_line(i);
			i++;
			display_prompt();
			ft_putstr(g_shell.current_line);
		}
		else if (key == K_UP || key == K_DOWN)
			ft_putendl("UP/DOWN");
		else if (key == K_RIGHT || key == K_LEFT)
			ft_putendl("RIGHT/LEFT");
		else if (key == K_DEL)
			ft_putendl("DEL");
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
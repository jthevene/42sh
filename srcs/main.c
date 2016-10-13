/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:20:49 by jules             #+#    #+#             */
/*   Updated: 2016/10/13 16:04:45 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

// static void		display_prompt(void)
// {
// 	ft_putstr("\033[32m$> \033[0m");
// }

// static	void	run_shell(void)
// {
// 	// int 	key;

// 	while (g_shell->running == 1)
// 	{
// 		g_shell->running = 1;
// 		ft_putstr("3");
// 		display_prompt();
// 		ft_putstr("4");
// 		// key = readkey();
// 		// if (key == K_RETURN)
// 		// 	handle_line();
// 		// if (key == K_PRINT)
// 			// ft_putchar_fd(key, 1);
// 		// else if (key == K_UP || key == K_DOWN)
// 		// else if (key == K_RIGHT || key == K_LEFT)
// 		// else if (key == K_SPACE)
// 		// else if (key == K_DEL)
// 		// else if (key == K_ESCAPE)
// 		g_shell->running = 0;
// 	}
// }

int		main(void)
{
	if (init_all())
		return (0);
	ft_putstr("init_all DONE/n");
	// run_shell();
	return (0);
}
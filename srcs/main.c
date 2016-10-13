/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:20:49 by jules             #+#    #+#             */
/*   Updated: 2016/10/13 10:35:54 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static void		display_prompt(void)
{
	ft_putstr("\033[32m$> \033[0m");
}

static	void	run_shell(void)
{
	while (42)
	{
		g_shell.running = 1;
		display_prompt();
		// if (read_stdin())
			// return ;
		// manage_line();
		g_shell.running = 0;
	}
}

int		main(void)
{
	if (init_all())
		return (0);
	run_shell();
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 16:49:40 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/22 08:58:07 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void		ft_exit(void)
{
	go_to_end();
	ft_putstr("\n");
	ft_reset_termios(g_shell.t_back);
	update_history_file(get_histsize("HISTFILESIZE"));
	free(g_shell.save_list);
	free_hist();
	exit(0);
}

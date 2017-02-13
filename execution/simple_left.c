/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:06:16 by jules             #+#    #+#             */
/*   Updated: 2017/02/13 12:38:35 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

int			simple_left(char *cmd, char *filename)
{
	FT_INIT(int, new_fd, 0);
	if ((new_fd = open(filename, O_RDONLY, 0600)) == -1)
	{
		ft_error(filename);
		return (0);
	}
	g_shell.left_redir_fd = new_fd;
	exec_function(cmd);
	g_shell.left_redir_fd = 0;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:06:16 by jules             #+#    #+#             */
/*   Updated: 2017/02/10 11:43:01 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

int 		simple_left(char *cmd, char *filename)
{
	FT_INIT(int, new_fd, 0);
	FT_INIT(char **, env_tab, lst_to_tab(g_shell.env));
	if ((new_fd = open(filename, O_RDONLY, 0600)) == -1)
	{
		ft_error(filename);
		return (1);
	}
	if ((new_fd = dup2(STDIN, new_fd)) == -1)
	{
		ft_error(filename);
		return (1);
	}
	if ((execve(cmd, filename, env_tab)) == -1)
	{
		ft_error(cmd);
		return (1);
	}
	close(new_fd);
}
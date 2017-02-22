/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_redirs_in_gshell.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 19:00:27 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/22 08:55:53 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int					fd_already_in_fdlist(t_fdlist **fdlist, int fd)
{
	while ((*fdlist)->prev)
		(*fdlist) = (*fdlist)->prev;
	while ((*fdlist))
	{
		if ((*fdlist)->fd_in == fd)
			return (1);
		if (!(*fdlist)->next)
			break ;
		(*fdlist) = (*fdlist)->next;
	}
	return (0);
}

void				stock_redirs_in_gshell(t_fdlist *fdlist)
{
	if (!fdlist)
		return ;
	while (fdlist->next)
		fdlist = fdlist->next;
	if (!push_right_redir(fdlist->filename, fdlist->fd_in, fdlist->fd_file, \
				&g_shell.right_redirs))
		return ;
	if (fdlist->prev)
		fdlist = fdlist->prev;
	else
		return ;
	while (fdlist)
	{
		if (!fd_already_in_fdlist(&g_shell.right_redirs, fdlist->fd_in))
		{
			if (!push_right_redir(fdlist->filename, fdlist->fd_in, \
						fdlist->fd_file, &g_shell.right_redirs))
				return ;
		}
		if (!fdlist->prev)
			break ;
		fdlist = fdlist->prev;
	}
}

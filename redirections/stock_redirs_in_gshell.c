/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_redirs_in_gshell.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 15:18:50 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:47 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 17:55:43 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/22 08:57:50 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void		free_aggreg(void)
{
	if (g_shell.aggreg)
	{
		while (g_shell.aggreg->prev)
			g_shell.aggreg = g_shell.aggreg->prev;
		FT_INIT(t_fdlist *, tmp, NULL);
		while (g_shell.aggreg)
		{
			tmp = g_shell.aggreg;
			g_shell.aggreg = g_shell.aggreg->next;
			free(tmp);
		}
		g_shell.aggreg = NULL;
	}
}

void		free_right_redir(void)
{
	if (g_shell.right_redirs)
		free_fdlist(&g_shell.right_redirs, 1);
	if (g_shell.left_redir_fd != -1)
		g_shell.left_redir_fd = -1;
}

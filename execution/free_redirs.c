/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:31 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

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

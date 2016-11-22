/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:55:54 by jules             #+#    #+#             */
/*   Updated: 2016/11/22 17:55:35 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	ft_histdel()
{
	if (g_shell.hist != NULL && *g_shell.hist != NULL)
	{
		while ((*g_shell.hist)->prev != NULL)
		{
			free(g_shell.hist->content);
			free(*g_shell.hist);
			*g_shell.hist = (*g_shell.hist)->prev;
		}
		free(g_shell.hist->content);
		free(*g_shell.hist);
		*g_shell.hist = NULL;
	}
	init_hist()
}
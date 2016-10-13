/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:53:52 by jules             #+#    #+#             */
/*   Updated: 2016/10/13 10:34:51 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		init_hist()
{
	g_shell.hist->content = NULL;
	g_shell.hist->next = NULL;
	g_shell.hist->prev = NULL;
}

void		ft_newhist(char *line)
{
	t_lst	*new_line;

	new_line = NULL;
	new_line->content = ft_strdup(line);
	new_line->next = NULL;
	new_line->prev = g_shell.hist;
	g_shell.hist->next = new_line;
	g_shell.hist = new_line;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:53:52 by jules             #+#    #+#             */
/*   Updated: 2016/10/18 14:33:42 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void		init_hist()
{
	if (!(g_shell.hist = (t_lst*)malloc(sizeof(t_list))))
	{
		ft_putstr("g_shell.hist malloc failed");
		exit(0);
	}
	g_shell.hist->content = NULL;
	g_shell.hist->next = NULL;
	g_shell.hist->prev = NULL;
}

void		ft_newhist(char *line)
{
	t_lst	*new_hist;
	
	new_hist = (t_lst *)malloc(sizeof(t_lst));
	if (new_hist)
	{
		new_hist->content = ft_strdup(line);
		new_hist->next = NULL;
		new_hist->prev = g_shell.hist;
		g_shell.hist->next = new_hist;
		g_shell.hist = new_hist;
	}
}
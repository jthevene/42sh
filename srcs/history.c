/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:53:52 by jules             #+#    #+#             */
/*   Updated: 2016/10/11 11:56:20 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

extern	t_env	g_env;

void		init_hist()
{
	g_env.hist->content = NULL;
	g_env.hist->next = NULL;
	g_env.hist->prev = NULL;
}

void		ft_newhist(char *line)
{
	t_lst	*newline;

	newline = NULL;
	newline->content = ft_strdup(line);
	newline->next = NULL;
	newline->prev = g_env.hist;
	g_env.hist->next = newline;
	g_env.hist = newline;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/30 14:52:21 by sgaudin           #+#    #+#             */
/*   Updated: 2016/10/13 10:56:00 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

int			fdlist_pushback(t_fdlist **fdlist, int key)
{
	FT_INIT(t_fdlist, *tmp, NULL);
	FT_INIT(t_fdlist, *new, NULL);
	if (!(*fdlist))
	{
		if (!((*fdlist) = (t_fdlist *)malloc(sizeof(t_fdlist))))
			return (0);
		(*fdlist)->prev = NULL;
		(*fdlist)->next = NULL;
	}
	else
	{
		if (!(new = (t_fdlist *)malloc(sizeof(t_fdlist))))
			return (0);
		new->next = NULL;
		new->key = key;
		while ((*fdlist)->next)
			(*fdlist) = (*fdlist)->next;
		tmp = (*fdlist);
		(*fdlist)->next = new;
		new->prev = tmp;
	}
	return (1);
}

void 		free_fdlist(t_fdlist **fdlist)
{
	t_fdlist	*tmp;
	t_fdlist	*tmp_n;

	tmp = (*fdlist);
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp->next)
	{
		close(tmp->key);
		tmp_n = tmp->next;
		free(tmp);
		tmp = tmp_n;
	}
	close(tmp->key);
	free(tmp);
	tmp = NULL;
	fdlist = NULL;
}

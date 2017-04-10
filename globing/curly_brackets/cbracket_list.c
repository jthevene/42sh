/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbracket_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 18:40:11 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:11 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int					clist_pushback(t_clist **clist)
{
	t_clist *new;
	t_clist *tmp;

	if (!(*clist))
	{
		if (!((*clist) = (t_clist *)malloc(sizeof(t_clist))))
			return (0);
		FT_MULTI3((*clist)->next, (*clist)->prev, NULL);
		(*clist)->list = NULL;
	}
	else
	{
		if (!(new = (t_clist *)malloc(sizeof(t_clist))))
			return (0);
		new->next = NULL;
		while ((*clist)->next)
			(*clist) = (*clist)->next;
		tmp = (*clist);
		(*clist)->next = new;
		new->prev = tmp;
		(*clist) = (*clist)->next;
		(*clist)->list = NULL;
	}
	return (1);
}

int					clist_list_pushback(t_clist **clist)
{
	t_bracket *new;
	t_bracket *tmp;

	if (!(*clist)->list)
	{
		if (!((*clist)->list = (t_bracket *)malloc(sizeof(t_bracket))))
			return (0);
		FT_MULTI3((*clist)->list->next, (*clist)->list->prev, NULL);
		(*clist)->list->content = NULL;
	}
	else
	{
		if (!(new = (t_bracket *)malloc(sizeof(t_bracket))))
			return (0);
		new->next = NULL;
		while ((*clist)->list->next)
			(*clist)->list = (*clist)->list->next;
		tmp = (*clist)->list;
		(*clist)->list->next = new;
		new->prev = tmp;
		(*clist)->list = (*clist)->list->next;
		(*clist)->list->content = NULL;
	}
	return (1);
}

void				rewind_tclist(t_clist **clist)
{
	while ((*clist)->prev)
	{
		rewind_tbracket(&(*clist)->list);
		(*clist) = (*clist)->prev;
	}
	rewind_tbracket(&(*clist)->list);
}

void				free_tclist(t_clist **list)
{
	FT_INIT(t_clist *, tmp, NULL);
	rewind_tclist(list);
	while ((*list)->next)
	{
		if ((*list)->list)
			free_tbracket(&(*list)->list);
		tmp = (*list);
		(*list) = (*list)->next;
		free(tmp);
	}
	if ((*list)->list)
		free_tbracket(&(*list)->list);
	tmp = (*list);
	(*list) = NULL;
	free(tmp);
}

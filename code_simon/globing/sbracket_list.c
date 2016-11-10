/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sbracket_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:40:25 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/04 14:40:29 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/globing.h"

int					sbracket_pushback(t_sbracket **list, int type)
{
	t_sbracket *tmp;
	t_sbracket *new;

	if (!(*list))
	{
		if (!((*list) = (t_sbracket *)malloc(sizeof(t_sbracket))))
			return (0);
		FT_MULTI3((*list)->next, (*list)->prev, NULL);
		(*list)->bracket = NULL;
		(*list)->type = type;
	}
	else
	{
		if (!(new = (t_sbracket *)malloc(sizeof(t_sbracket))))
			return (0);
		new->next = NULL;
		while ((*list)->next)
			(*list) = (*list)->next;
		tmp = (*list);
		(*list)->next = new;
		new->prev = tmp;
		(*list) = (*list)->next;
		(*list)->bracket = NULL;
		(*list)->type = type;
	}
	return (1);
}

void			print_sbracket(t_sbracket *list)
{
	while (list->prev)
		list = list->prev;
	while (list->next)
	{
		printf("bracket = %s\n", list->bracket);
		list = list->next;
	}
	printf("bracket = %s\n", list->bracket);
}
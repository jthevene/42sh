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

#include "../../includes/globing.h"

int					sbracket_pushback(t_sbracket **list)
{
	t_sbracket *tmp;
	t_sbracket *new;

	if (!(*list))
	{
		if (!((*list) = (t_sbracket *)malloc(sizeof(t_sbracket))))
			return (0);
		FT_MULTI3((*list)->next, (*list)->prev, NULL);
		(*list)->bracket = NULL;
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
	}
	return (1);
}

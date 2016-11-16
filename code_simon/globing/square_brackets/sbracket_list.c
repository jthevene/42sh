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

int					bracket_pushback(t_bracket **list)
{
	t_bracket *tmp;
	t_bracket *new;

	if (!(*list))
	{
		if (!((*list) = (t_bracket *)malloc(sizeof(t_bracket))))
			return (0);
		FT_MULTI3((*list)->next, (*list)->prev, NULL);
		(*list)->content = NULL;
	}
	else
	{
		if (!(new = (t_bracket *)malloc(sizeof(t_bracket))))
			return (0);
		new->next = NULL;
		while ((*list)->next)
			(*list) = (*list)->next;
		tmp = (*list);
		(*list)->next = new;
		new->prev = tmp;
		(*list) = (*list)->next;
		(*list)->content = NULL;
	}
	return (1);
}

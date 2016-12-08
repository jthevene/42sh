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
	FT_INIT(t_bracket, *tmp, NULL);
	FT_INIT(t_bracket, *new, NULL);
	if (!(*list))
	{
		if (!((*list) = (t_bracket *)malloc(sizeof(t_bracket))))
			return (0);
		(*list)->prev =  NULL;
		(*list)->next = NULL;
		(*list)->content = NULL;
	}
	else
	{
		if (!(new = (t_bracket *)malloc(sizeof(t_bracket))))
			return (0);
//		ft_putstr("TEST SIGV 1\n");
		new->next = NULL;
//		ft_putstr("TEST SIGV 2\n");
		while ((*list)->next != NULL)
		{
//			ft_putstr("TEST SIGV 3\n");
			(*list) = (*list)->next;
		}
		tmp = (*list);
		(*list)->next = new;
		new->prev = tmp;
		(*list) = (*list)->next;
		(*list)->content = NULL;
	}
	return (1);
}

int				pushback_content(t_bracket **list, char *content)
{
	if (!bracket_pushback(list))
		return (0);
	(*list)->content = content;
	return (1);
}

void			rewind_tbracket(t_bracket **list)
{
	if ((*list) != NULL)
	{
		while ((*list)->prev)
			(*list) = (*list)->prev;
	}
}

void			free_tbracket(t_bracket **list)
{
	FT_INIT(t_bracket *, tmp, NULL);
	while ((*list)->prev)
		(*list) = (*list)->prev;
	while ((*list)->next)
	{
		if ((*list)->content)
			free((*list)->content);
		tmp = (*list);
		(*list) = (*list)->next;
		free(tmp);
	}
	if ((*list)->content)
		free((*list)->content);
	tmp = (*list);
	(*list) = NULL;
	free(tmp);
}
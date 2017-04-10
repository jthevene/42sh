/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sbracket_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 18:40:11 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:57:52 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int				bracket_pushback(t_bracket **list)
{
	FT_INIT(t_bracket, *tmp, NULL);
	FT_INIT(t_bracket, *new, NULL);
	if (!(*list))
	{
		if (!((*list) = (t_bracket *)malloc(sizeof(t_bracket))))
			return (0);
		(*list)->prev = NULL;
		(*list)->next = NULL;
		(*list)->content = NULL;
	}
	else
	{
		if (!(new = (t_bracket *)malloc(sizeof(t_bracket))))
			return (0);
		new->next = NULL;
		new->content = NULL;
		while ((*list)->next)
			(*list) = (*list)->next;
		tmp = (*list);
		new->prev = tmp;
		(*list)->next = new;
		(*list) = (*list)->next;
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
	if (list != NULL && (*list))
	{
		while ((*list)->prev)
			(*list) = (*list)->prev;
	}
}

int				free_tbracket(t_bracket **list)
{
	FT_INIT(t_bracket *, tmp, NULL);
	if ((*list))
	{
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
	return (1);
}

void			copy_list(t_bracket **src, t_bracket **dest)
{
	rewind_tbracket(&(*src));
	while ((*src)->next)
	{
		pushback_content(&(*dest), ft_strdup((*src)->content));
		(*src) = (*src)->next;
	}
	pushback_content(&(*dest), ft_strdup((*src)->content));
	rewind_tbracket(&(*src));
	rewind_tbracket(&(*dest));
}

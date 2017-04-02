/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_lst_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:11 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int			secured_call_to_sbracket(t_glob *g, char *s, t_lst **f)
{
	hub_sbracket(g, s);
	if (!g->sbracket)
	{
		ft_lst_free(&(*f));
		free_triple_str(&g->f_path, &g->l_path, NULL);
		return (0);
	}
	rewind_tbracket(&g->sbracket);
	return (1);
}

void		ft_lst_free(t_lst **list)
{
	FT_INIT(t_lst *, tmp, NULL);
	if ((*list))
	{
		ft_lst_rewind(list);
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
}

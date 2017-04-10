/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_lst_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 10:32:10 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:57:43 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

int			secured_call_to_sbracket(t_glob *g, char *s, t_lst **f
									, char **token)
{
	hub_sbracket(g, s);
	if ((ft_strchr(s, '[') || ft_strchr(s, ']')) && !g->sbracket)
	{
		ft_lst_free(&(*f));
		free_triple_str(&g->f_path, &g->l_path, &(*token));
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

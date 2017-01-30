/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_lst_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:50:18 by sgaudin           #+#    #+#             */
/*   Updated: 2017/01/30 10:50:19 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/globing.h"

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

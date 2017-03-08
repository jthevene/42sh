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

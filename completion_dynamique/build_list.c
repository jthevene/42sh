/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <dvirgile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by dvirgile          #+#    #+#             */
/*   Updated: 2017/03/03 13:29:28 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

t_completion	*change_col(t_completion *all_col, t_completion *head,
					int *ref_col, int nb_elem)
{
	(*ref_col)++;
	if (all_col && all_col->next)
		all_col = all_col->next;
	else
	{
		if (nb_elem)
		{
			*ref_col = 0;
			all_col = head;
			if (all_col && all_col->next)
				ft_putendl("");
		}
	}
	return (all_col);
}

t_completion	*create_cell(t_file *elem)
{
	FT_INIT(t_completion *, new_cell, NULL);
	new_cell = (t_completion*)malloc(sizeof(t_completion));
	new_cell->elem = elem;
	new_cell->next = NULL;
	return (new_cell);
}

static t_file	*build_col(t_file **match_files, int nb_elem_lst)
{
	FT_INIT(t_file *, col, NULL);
	FT_INIT(t_file *, head_col, NULL);
	while (match_files && (*match_files) && nb_elem_lst > 0)
	{
		if (!col)
			MULTI(head_col, col, (*match_files));
		else
		{
			col->next = (*match_files);
			col = col->next;
		}
		nb_elem_lst--;
		(*match_files) = (*match_files)->next;
	}
	if (col)
		col->next = NULL;
	return (head_col);
}

t_completion	*build_lst_lst(t_file *match_files, int nb_elem, int nb_col)
{
	FT_INIT(t_completion *, all_col, NULL);
	FT_INIT(t_completion *, head_all_col, NULL);
	FT_INIT(t_file *, tmp, NULL);
	while (match_files && nb_col > 0)
	{
		tmp = build_col(&match_files, nb_elem);
		if (!all_col)
			MULTI(head_all_col, all_col, create_cell(tmp));
		else
		{
			all_col->next = create_cell(tmp);
			all_col = all_col->next;
		}
		nb_col--;
	}
	all_col->next = NULL;
	return (head_all_col);
}

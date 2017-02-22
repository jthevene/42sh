/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_auto_completion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 17:18:44 by dvirgile          #+#    #+#             */
/*   Updated: 2017/02/22 08:58:01 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void			free_lists(t_file *match_files)
{
	FT_INIT(t_file*, tmp, NULL);
	if (!match_files)
		return ;
	while (match_files)
	{
		ft_strdel(&(match_files->name));
		ft_strdel(&(match_files->absolute_path));
		tmp = match_files;
		match_files = match_files->next;
		free(tmp);
	}
}

void			free_lst_lst(t_completion *lst_lst)
{
	FT_INIT(t_completion*, tmp_lst, NULL);
	while (lst_lst->next)
	{
		tmp_lst = lst_lst;
		lst_lst = lst_lst->next;
		free(tmp_lst);
	}
	free(lst_lst);
}

void			free_files(t_file **files_list)
{
	FT_INIT(t_file*, tmp, NULL);
	if (!(*files_list))
		return ;
	while ((*files_list))
	{
		ft_strdel(&((*files_list)->name));
		ft_strdel(&((*files_list)->absolute_path));
		tmp = (*files_list);
		(*files_list) = (*files_list)->next;
		free(tmp);
	}
}

void			free_auto_tab(char **table)
{
	int		colonne;

	colonne = 0;
	while ((table) && (table)[colonne])
	{
		free((table)[colonne]);
		(table)[colonne] = NULL;
		colonne++;
	}
	free(table);
}

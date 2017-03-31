/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_auto_completion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:40 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

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

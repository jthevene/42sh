/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:40 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

static	int			compare(char *str1, char *str2)
{
	FT_INIT(int, diff, 0);
	FT_INIT(char*, s1, str1);
	FT_INIT(char*, s2, str2);
	diff = ft_strcmp(s1, s2);
	return (diff);
}

t_file				*sort_list(t_file *files)
{
	FT_INIT(t_file*, after, files);
	FT_INIT(t_file*, before, files);
	FT_INIT(t_file*, tmp, NULL);
	while (after && after->next)
	{
		if (compare(after->name, (after->next)->name) > 0)
		{
			files = (after == files) ? after->next : files;
			before->next = after->next;
			tmp = (after->next)->next;
			(after->next)->next = after;
			after->next = tmp;
			MULTI(after, before, files);
		}
		else
		{
			before = after;
			after = after->next;
		}
	}
	return (files);
}

static t_file		*create_cell(char *name, int dir, char *path_file)
{
	t_file			*new_cell;

	new_cell = (t_file *)malloc(sizeof(t_file));
	new_cell->type = dir ? 1 : 0;
	new_cell->name = dir ? ft_strjoin(name, "/") : ft_strdup(name);
	new_cell->len = ft_strlen(new_cell->name);
	new_cell->nb_elem = 0;
	new_cell->absolute_path = ft_strdup(path_file);
	new_cell->next = NULL;
	return (new_cell);
}

int					verif_file_match(char *to_search, char *file)
{
	if (!to_search || !file)
		return (0);
	if (!ft_strlen(to_search) && file[0] == '.')
		return (0);
	if (!ft_strcmp(file, ".") || !ft_strcmp(file, ".."))
		if (ft_strcmp(to_search, ".") && ft_strcmp(to_search, ".."))
			return (0);
	if (ft_strlen(to_search) <= ft_strlen(file) &&
		!ft_strncmp(file, to_search, ft_strlen(to_search)))
		return (1);
	else
		return (0);
}

t_file				*store_files_dirs(DIR *rep, t_file *files,
					char *path, char *to_search)
{
	struct dirent	*fd;
	struct stat		infos;

	FT_INIT(t_file *, start, NULL);
	FT_INIT(char*, path_file, NULL);
	FT_INIT(char*, tmp, ft_strjoin(path, path[ft_strlen(path) - 1]
							!= '/' ? "/" : ""));
	while ((fd = readdir(rep)))
	{
		if (verif_file_match(to_search, fd->d_name))
			path_file = ft_strjoin(tmp, fd->d_name);
		if (!files && path_file && !stat(path_file, &infos))
			MULTI(start, files, create_cell(fd->d_name,
				S_ISDIR(infos.st_mode), path_file));
		else if (path_file && !stat(path_file, &infos))
		{
			files->next = create_cell(fd->d_name, S_ISDIR(infos.st_mode)
				, path_file);
			files = files->next;
		}
		if (path_file)
			ft_strdel(&path_file);
	}
	ft_strdel(&tmp);
	return (start);
}

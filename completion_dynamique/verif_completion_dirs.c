/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_completion_dirs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:36 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

static int			verif_access_auto(char *path)
{
	struct stat infos;

	lstat(path, &infos);
	if (access(path, F_OK) != 0)
		return (0);
	else if (S_ISLNK(infos.st_mode))
		return (1);
	else if (!S_ISDIR(infos.st_mode) && !S_ISLNK(infos.st_mode))
		return (0);
	else if (access(path, X_OK) != 0)
		return (0);
	return (1);
}

static char			*path_str(char **str_path, char *str, int j)
{
	FT_INIT(char*, tmp, NULL);
	if (str && j != -1 && verif_access_auto(str))
	{
		tmp = *str_path;
		*str_path = ft_strjoin(*str_path, ":");
		ft_strdel(&tmp);
		tmp = *str_path;
		*str_path = ft_strjoin(*str_path, str);
		ft_strdel(&tmp);
	}
	return (*str_path);
}

static char			**reject_unfairs(char **tabl)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	FT_INIT(char*, str_path, ft_strdup(""));
	FT_INIT(char**, new_tabl, NULL);
	while (tabl[i] && j <= len_tab(tabl))
	{
		while (j <= len_tab(tabl) && tabl[i] && tabl[j])
		{
			if (j != i && !ft_strcmp(tabl[i], tabl[j]))
			{
				j = -1;
				break ;
			}
			else
				j++;
		}
		str_path = path_str(&str_path, tabl[i], j);
		i++;
		j = i + 1;
	}
	new_tabl = ft_strsplit(str_path, ':');
	ft_strdel(&str_path);
	return (new_tabl);
}

char				**clear_path(char **sentence)
{
	FT_INIT(char*, tmp, NULL);
	tmp = *sentence;
	if (ft_strrchr(*sentence, ' ') && ft_strrchr(*sentence, ' ') + 1)
	{
		*sentence = ft_strdup(ft_strrchr(*sentence, ' ') + 1);
		ft_strdel(&tmp);
	}
	return (sentence);
}

char				**verif_dirs(char **tabl)
{
	FT_INIT(char**, tmp, tabl);
	if (!tabl)
		return (NULL);
	tabl = reject_unfairs(tabl);
	free_tab(tmp);
	return (tabl);
}

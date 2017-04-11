/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path_second_part.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <dvirgile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/11 12:18:24 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

static char			*add_slash(char *second_str, char *first_str,
					char **sentence, int len)
{
	FT_INIT(char*, tmp, NULL);
	if ((*sentence)[len] != '/')
	{
		len = ft_strlen(second_str) -
			ft_strlen(ft_strrchr(second_str, '/')) + 1;
		tmp = ft_strnew(len);
		ft_strncpy(tmp, second_str, len);
		ft_strdel(&second_str);
		second_str = tmp;
	}
	else
	{
		first_str = second_str;
		second_str = ft_strjoin(second_str, "/");
		ft_strdel(&first_str);
		ft_strdel(sentence);
		*sentence = ft_strdup("");
	}
	return (second_str);
}

static	char		*verif_second_str(struct stat infos, char *second_str,
					char *first_str, char **sentence)
{
	FT_INIT(char*, tmp, NULL);
	FT_INIT(int, len, ft_strlen(*sentence) - 1);
	ft_strdel(&first_str);
	if (S_ISDIR(infos.st_mode) && second_str[ft_strlen(second_str) - 1] != '/')
		second_str = add_slash(second_str, first_str, sentence, len);
	else
	{
		len = ft_strlen(second_str) -
			ft_strlen(ft_strrchr(second_str, '/')) + 1;
		tmp = ft_strnew(len);
		ft_strncpy(tmp, second_str, len);
		ft_strdel(&second_str);
		second_str = tmp;
	}
	return (second_str);
}

static char			*first_str_val(char *first_str, char **second_str,
					struct stat infos)
{
	if (first_str && !lstat(first_str, &infos) && S_ISDIR(infos.st_mode) &&
		first_str[ft_strlen(first_str) - 1] != '/')
	{
		*second_str = first_str;
		first_str = ft_strjoin(first_str, "/");
		ft_strdel(second_str);
	}
	return (first_str);
}

int					verif_bins(char *sentence)
{
	FT_INIT(char**, points, ft_strsplit(sentence, '/'));
	FT_INIT(int, i, 0);
	while (points && points[i])
	{
		if (ft_strstr(points[i], "..") || !ft_strcmp(points[i], "."))
		{
			free_tab(points);
			return (1);
		}
		i++;
	}
	if (points)
		free_tab(points);
	return (0);
}

char				*set_end_path(char **new_path, char **sentence)
{
	struct stat		infos;

	FT_INIT(char *, second_str, (*new_path));
	FT_INIT(char *, first_str, NULL);
	if (!(*new_path) || !ft_strrchr((*new_path), '/'))
		return ((*new_path));
	first_str = ft_strsub((*new_path), 0, ft_strlen((*new_path)) -
		(ft_strlen(ft_strrchr((*new_path), '/')) - 1));
	if (lstat(second_str, &infos) == 0)
		return (verif_second_str(infos, second_str, first_str, sentence));
	if (lstat(first_str, &infos) == -1)
	{
		ft_strdel(&first_str);
		ft_strdel(&second_str);
		return (NULL);
	}
	else
		ft_strdel(new_path);
	first_str = first_str_val(first_str, &second_str, infos);
	return (first_str);
}

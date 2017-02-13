/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_converter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 16:53:18 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/13 12:38:53 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static	char		*set_begining(char *sentence, char *home,
					char *current_path)
{
	FT_INIT(char*, new_path, ft_strnew(ft_strlen(sentence) + 100));
	if (ft_strlen(sentence) && !ft_strcmp(sentence, "."))
	{
		ft_strcpy(new_path, current_path);
		ft_strcat(new_path, sentence + 1);
	}
	else if (sentence[0] == '~')
	{
		ft_strcpy(new_path, home);
		ft_strcat(new_path, sentence + 1);
	}
	else if (!ft_strcmp(sentence, ".."))
	{
		ft_strncpy(new_path, current_path, ft_strlen(current_path) -
			ft_strlen(ft_strrchr(current_path, '/')));
		ft_strcat(new_path, "/");
	}
	else
	{
		ft_strcpy(new_path, current_path);
		ft_strcat(new_path, "/");
		ft_strcat(new_path, sentence);
	}
	return (new_path);
}

void				remove_last_dir(char **str, char c)
{
	if (!str || !c)
		return ;
	FT_INIT(int, i, 0);
	FT_INIT(int, nb_slash, 0);
	while ((*str)[i])
	{
		if ((*str)[i] == c)
			nb_slash++;
		i++;
	}
	i--;
	while ((*str)[i] && (*str)[i] == c)
	{
		(*str)[i] = '\0';
		i--;
	}
	while ((*str)[i] && (*str)[i] != c)
	{
		(*str)[i] = '\0';
		i--;
	}
	if (nb_slash < 1)
		(*str)[0] = '/';
}

static char			*parse_dirs(char **dirs_tab, char *home, int len_sentence)
{
	FT_INIT(int, i, 0);
	FT_INIT(char*, str, ft_strcpy(ft_strnew(len_sentence + 100), "/"));
	while (dirs_tab && dirs_tab[i])
	{
		if (!ft_strcmp(dirs_tab[i], "~"))
			ft_strcat(str, home);
		else if (!ft_strcmp(dirs_tab[i], ".."))
			remove_last_dir(&str, '/');
		else if (!ft_strcmp(dirs_tab[i], "."))
			;
		else
		{
			ft_strcat(str, dirs_tab[i]);
			if ((dirs_tab[i + 1] && str[ft_strlen(str) - 1] != '/'))
				ft_strcat(str, "/");
		}
		i++;
	}
	return (str);
}

char				*path_converter(char *sentence, char *home, char *pwd)
{
	FT_INIT(char*, str, NULL);
	FT_INIT(char**, dirs_tab, NULL);
	if (sentence[0] != '/')
		str = set_begining(sentence, home, pwd);
	dirs_tab = ft_strsplit(str ? str : sentence, '/');
	ft_strdel(&str);
	str = parse_dirs(dirs_tab, home, ft_strlen(sentence));
	free_auto_tab(dirs_tab);
	return (str);
}

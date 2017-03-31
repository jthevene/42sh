/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_converter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:44 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

static	char		*set_begining_sec(char **pwd, char **new_path,
					char *current_path, char *sentence)
{
	if (!ft_strcmp(sentence, ".."))
	{
		if (!(*pwd))
		{
			free(*new_path);
			return (ft_rescue_directory());
		}
		else
		{
			ft_strncpy(*new_path, current_path, ft_strlen(current_path) -
				ft_strlen(ft_strrchr(current_path, '/')));
			ft_strcat(*new_path, "/");
		}
	}
	else
	{
		ft_strcpy(*new_path, current_path);
		ft_strcat(*new_path, "/");
		ft_strcat(*new_path, sentence);
	}
	return (*new_path);
}

static	char		*set_begining(char *sentence, char *home,
					char *current_path, char *new_path)
{
	FT_INIT(char*, pwd, getcwd(NULL, 1024));
	if (ft_strlen(sentence) && !ft_strcmp(sentence, "."))
	{
		if (!pwd)
		{
			ft_putstr("cd: error retrieving current directory: getcwd: ");
			ft_putstr("cannot access parent directories: No such file or");
			ft_putstr(" directory\n");
			ft_strdel(&new_path);
		}
		else
		{
			ft_strcpy(new_path, current_path);
			ft_strcat(new_path, sentence + 1);
		}
	}
	else if (sentence[0] == '~')
	{
		ft_strcpy(new_path, home);
		ft_strcat(new_path, sentence + 1);
	}
	else
		new_path = set_begining_sec(&pwd, &new_path, current_path, sentence);
	free(pwd);
	return (new_path);
}

void				remove_last_dir(char **str, char c)
{
	if (!str || !c)
		return ;
	FT_INIT(int, i, 0);
	FT_INIT(int, nb_slash, 0);
	while ((*str) && i >= 0 && (*str)[i])
	{
		if ((*str)[i] == c)
			nb_slash++;
		i++;
	}
	i--;
	while ((*str) && i >= 0 && (*str)[i] && (*str)[i] == c)
	{
		(*str)[i] = '\0';
		i--;
	}
	while ((*str) && i >= 0 && (*str)[i] && (*str)[i] != c)
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
		if (!(str = set_begining(sentence, home, pwd,
			ft_strnew(ft_strlen(sentence) + 100))))
			return (NULL);
	dirs_tab = ft_strsplit(str ? str : sentence, '/');
	ft_strdel(&str);
	str = parse_dirs(dirs_tab, home, ft_strlen(sentence));
	free_auto_tab(dirs_tab);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:35:42 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

static	char		*set_begining(char *sentence, char *home,
					char *current_path)
{
	FT_INIT(char*, new_path, NULL);
	FT_INIT(char*, tmp, NULL);
	if (ft_strlen(sentence) >= 2 && !ft_strncmp(sentence, "./", 2))
		new_path = ft_strjoin(current_path, sentence + 1);
	else if (sentence[0] == '~')
		new_path = ft_strjoin(home, sentence + 1);
	else if (!ft_strcmp(sentence, ".."))
	{
		new_path = ft_strsub(current_path, 0, ft_strlen(current_path) -
			ft_strlen(ft_strrchr(current_path, '/')));
		tmp = new_path;
		new_path = ft_strjoin(new_path, "/");
		free(tmp);
	}
	else
	{
		new_path = ft_strjoin(current_path, "/");
		tmp = new_path;
		new_path = ft_strjoin(new_path, sentence);
		free(tmp);
	}
	return (new_path);
}

static void			remove_char(char **str, char c)
{
	if (!str || !c)
		return ;
	FT_INIT(int, i, ft_strlen(*str) - 1);
	while ((*str)[i] && (*str)[i] == c)
	{
		(*str)[i] = '\0';
		i--;
	}
}

static	char		*parse_dirs(char **dirs, char *new_path, char *home)
{
	while (dirs && *dirs)
	{
		if (!ft_strcmp(*dirs, "~"))
			ft_strcat(new_path, home);
		else if (!ft_strcmp(*dirs, ".."))
		{
			remove_char(&new_path, '/');
			ft_bzero((void*)(new_path + (ft_strlen(new_path) -
			ft_strlen(ft_strrchr(new_path, '/')))), ft_strlen(new_path));
			if (!ft_strlen(new_path))
				ft_strcpy(new_path, "/");
		}
		else if (!ft_strcmp(*dirs, "."))
			;
		else
		{
			if (new_path[ft_strlen(new_path) - 1] != '/')
				ft_strcat(new_path, "/");
			ft_strcat(new_path, *dirs);
		}
		if ((*(dirs + 1) && new_path[ft_strlen(new_path) - 1] != '/'))
			ft_strcat(new_path, "/");
		(dirs)++;
	}
	return (new_path);
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

int			verif_access_auto(char *path)
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

char 		*path_str(char** str_path, char *str, int j)
{
	FT_INIT(char*, tmp, NULL);
	if (j != -1 && verif_access_auto(str))
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

char 		**reject_doublons(char **tabl)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	FT_INIT(char*, str_path, ft_strdup(""));
	FT_INIT(char**, new_tabl, NULL);
	while (tabl[i] && j <= len_tab(tabl))
	{
		while (tabl[i] && tabl[j])
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

char 		**verif_dirs(char **tabl)
{
	FT_INIT(char**, tmp, tabl);
	if (!tabl)
		return (NULL);
	tabl = reject_doublons(tabl);
	free_tab(tmp);
	return (tabl);
}

char				**set_path(char **sentence, char *home, char *c_path)
{
	FT_INIT(char*, new_path, NULL);
	FT_INIT(char**, dirs, NULL);
	home = !home ? "" : home;
	c_path = !c_path ? "" : c_path;
	if ((*sentence)[ft_strlen(*sentence) - 1] == ' ')
		return (ft_strsplit(c_path, '\n'));
	if (!ft_strchr(*sentence, ' ') && *sentence[0] != '/' && ft_strlen(c_path))
	{
		new_path = get_var(&g_shell, "PATH");
		dirs = verif_dirs(ft_strsplit(new_path, ':'));
		ft_strdel(&new_path);
		return (dirs);
	}
	else
		sentence = clear_path(sentence);
	new_path = set_begining(*sentence, home, *sentence[0] == '/' ? "" : c_path);
	dirs = ft_strsplit(new_path, '/');
	ft_bzero((void*)new_path, ft_strlen(new_path));
	ft_strcat(new_path, "/");
	new_path = parse_dirs(dirs, new_path, home);
	free_tab(dirs);
	new_path = set_end_path(&new_path, sentence);
	dirs = verif_dirs(ft_strsplit(new_path, '\n'));
	ft_strdel(&new_path);
	return (dirs);
}

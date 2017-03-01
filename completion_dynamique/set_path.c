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
	while (i >= 0 && (*str)[i] && (*str)[i] == c)
	{
		(*str)[i] = '\0';
		i--;
	}
}

static	char		*parse_dirs(char **dirs, char *new_p, char *home)
{
	while (dirs && *dirs)
	{
		if (!ft_strcmp(*dirs, "~"))
			ft_strcat(new_p, home);
		else if (!ft_strcmp(*dirs, ".."))
		{
			remove_char(&new_p, '/');
			ft_bzero((void*)(new_p + (ft_strlen(new_p) -
			ft_strlen(ft_strrchr(new_p, '/')))), ft_strlen((new_p
			+ (ft_strlen(new_p) - ft_strlen(ft_strrchr(new_p, '/'))))));
			new_p = !ft_strlen(new_p) ? ft_strcpy(new_p, "/") : new_p;
		}
		else if (!ft_strcmp(*dirs, "."))
			;
		else
		{
			if (new_p[ft_strlen(new_p) - 1] != '/')
				ft_strcat(new_p, "/");
			ft_strcat(new_p, *dirs);
		}
		if ((*(dirs + 1) && new_p[ft_strlen(new_p) - 1] != '/'))
			ft_strcat(new_p, "/");
		(dirs)++;
	}
	return (new_p);
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

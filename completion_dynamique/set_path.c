/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <dvirgile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/10 11:42:57 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

static	char	*set_begining(char *sentence, char *home,
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

static void		remove_char(char **str, char c)
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

static	char	*parse_dirs(char **dirs, char *new_p, char *home)
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

static char		**complete_char(char **new_path, char *home,
					char **sentence, int slash)
{
	FT_INIT(char**, dirs, NULL);
	dirs = ft_strsplit(*new_path, '/');
	ft_bzero((void*)*new_path, ft_strlen(*new_path));
	ft_strcat(*new_path, "/");
	*new_path = parse_dirs(dirs, *new_path, home);
	ft_strcat(*new_path, slash ? "/" : "");
	free_tab(dirs);
	*new_path = set_end_path(new_path, sentence);
	dirs = verif_dirs(ft_strsplit(*new_path, '\n'));
	ft_strdel(new_path);
	return (dirs);
}

char			**set_path(char **sentence, char *home, char *c_path,
				bool detect_bins)
{
	FT_INIT(char*, new_path, NULL);
	FT_INIT(char**, dirs, NULL);
	home = !home ? "" : home;
	c_path = !c_path ? "" : c_path;
	if ((*sentence)[ft_strlen(*sentence) - 1] == ' ')
		return (ft_strsplit(c_path, '\n'));
	if (detect_bins && !ft_strchr(*sentence, ' ')
		&& *sentence[0] != '/' && ft_strlen(c_path) && !verif_bins(*sentence))
	{
		new_path = get_var(g_shell.env, "PATH");
		dirs = verif_dirs(ft_strsplit(new_path, ':'));
		ft_strdel(&new_path);
		return (dirs);
	}
	else
		sentence = clear_path(sentence);
	new_path = set_begining(*sentence, home, *sentence[0] == '/' ?
				"" : c_path);
	FT_INIT(int, slash, new_path[ft_strlen(new_path) - 1] == '/' ? 1 : 0);
	dirs = complete_char(&new_path, home, sentence, slash);
	return (dirs);
}

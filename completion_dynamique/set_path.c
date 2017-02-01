/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 17:19:24 by dvirgile          #+#    #+#             */
/*   Updated: 2017/01/16 17:19:37 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

static	char		*set_begining(char *sentence, char *home,
					char *current_path)
{
	FT_INIT(char*, new_path, ft_strnew(ft_strlen(sentence) + 100));
	if (ft_strlen(sentence) >= 2 && !ft_strncmp(sentence, "./", 2))
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

char				**set_path(char **sentence, char *home, char *current_path)
{
	FT_INIT(char*, new_path, NULL);
	FT_INIT(char**, dirs, NULL);
	home = !home ? "" : home;
	current_path = !current_path ? "" : current_path;
	if ((*sentence)[ft_strlen(*sentence) - 1] == ' ')
		return (ft_strsplit(current_path, '\n'));
	if (!ft_strchr(*sentence, ' ') && *sentence[0] != '/'
		&& ft_strlen(current_path))
		return (ft_strsplit(get_var(&g_shell, "PATH"), ':'));
	else
		sentence = clear_path(sentence);
	new_path = set_begining(*sentence, home, *sentence[0] == '/' ? ""
		: current_path);
	dirs = ft_strsplit(new_path, '/');
	ft_bzero((void*)new_path, ft_strlen(new_path));
	ft_strcat(new_path, "/");
	new_path = parse_dirs(dirs, new_path, home);
	free_auto_tab(dirs);
	new_path = set_end_path(&new_path, sentence);
	dirs = ft_strsplit(new_path, '\n');
	ft_strdel(&new_path);
	return (dirs);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_converter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:36:50 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

char 					*ft_rescue_directory(void)
{
	if (!g_shell.line)
		return (NULL);
	FT_INIT(char*, path_rescue, ft_strdup(g_shell.line));
	FT_INIT(char*, tmp, NULL);
	if (!verif_access_bin_directory_(path_rescue))
	{
		if (path_rescue && ft_strrchr(path_rescue, '/'))
		{
			tmp = ft_strsub(path_rescue, 0, ft_strlen(path_rescue) -
				ft_strlen(ft_strrchr(path_rescue, '/')));
			ft_strdel(&path_rescue);
			path_rescue = ft_strjoin(tmp, "/");
		}
	}
	if (verif_access_bin_directory_(path_rescue))
		return (path_rescue);
	return (ft_strdup(g_shell.line));
}

static	char		*set_begining(char *sentence, char *home,
					char *current_path)
{
	FT_INIT(char*, new_path, ft_strnew(ft_strlen(sentence) + 100));
	if (ft_strlen(sentence) && !ft_strcmp(sentence, "."))
	{
		if (!getcwd(NULL, 1024))
		{
			ft_putstr("cd: error retrieving current directory: getcwd: ");
			ft_putstr("cannot access parent directories: No such file or");
			ft_putstr(" directory\n");
			free(new_path);
			return (NULL);
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
	else if (!ft_strcmp(sentence, ".."))
	{
		if (!getcwd(NULL, 1024))
		{
			free(new_path);
			return (ft_rescue_directory());
		}
		else
		{
			ft_strncpy(new_path, current_path, ft_strlen(current_path) -
				ft_strlen(ft_strrchr(current_path, '/')));
			ft_strcat(new_path, "/");
		}
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
		if (!(str = set_begining(sentence, home, pwd)))
			return (NULL);		
	dirs_tab = ft_strsplit(str ? str : sentence, '/');
	ft_strdel(&str);
	str = parse_dirs(dirs_tab, home, ft_strlen(sentence));
	free_auto_tab(dirs_tab);
	return (str);
}

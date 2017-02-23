/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 11:29:38 by dvirgile          #+#    #+#             */
/*   Updated: 2017/02/22 08:58:10 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

static char			**verif_args_cd(char *line, int *len_tab)
{
	FT_INIT(char**, tab_line, lsh_read_line(line));
	while (tab_line && tab_line[*len_tab])
		(*len_tab)++;
	if (ft_strcmp(tab_line[0], "cd") || (*len_tab) > 3)
	{
		free_auto_tab(tab_line);
		tab_line = NULL;
	}
	if (tab_line && *len_tab == 3 && (ft_strcmp(tab_line[1], "-P")
		&& ft_strcmp(tab_line[1], "-L")))
	{
		ft_putstr_fd("cd: error arguments\nTry cd [-L|-P] [dir]\n", 2);
		ft_putstr_fd("Options:\n-L	force symbolic links to be followed\n", 2);
		ft_putstr_fd("-P	use the physical directory structure ", 2);
		ft_putstr_fd("without following symbolic links\n", 2);
		free_tab(tab_line);
		return (NULL);
	}
	if ((*len_tab) > 3)
		ft_putstr_fd("cd: too many arguments\n", 2);
	return (tab_line);
}

static void			set_option_sentence(char **sentence, char **option,
					int len_tab, char **tab_line)
{
	*option = "";
	if (len_tab == 3)
	{
		*option = tab_line[1];
		*sentence = ft_strdup(tab_line[2]);
	}
	else if (len_tab == 2)
	{
		if (!ft_strcmp(tab_line[1], "-"))
			*sentence = get_var(&g_shell, "OLDPWD");
		else
			*sentence = ft_strdup(tab_line[1]);
	}
	else if (len_tab == 1)
		*sentence = get_var(&g_shell, "HOME");
	else
		*sentence = ft_strdup("");
}

static void			in_dir(char *path, char *pwd)
{
	FT_INIT(char*, tmp, NULL);
	if (chdir(path))
		ft_putstr_fd("Error chdir\n", 2);
	else
	{
		if (path[ft_strlen(path) - 1] == '/')
			path[ft_strlen(path) - 1] = '\0';
		tmp = ft_strjoin("setenv PWD=", path);
		ft_setenv(tmp);
		ft_strdel(&tmp);
		tmp = ft_strjoin("setenv OLDPWD=", pwd);
		ft_setenv(tmp);
		ft_strdel(&tmp);
	}
}

static void			go_to_dir(int cas, char **path, char *home, char *file_name)
{
	FT_INIT(char*, tmp, NULL);
	if (!cas)
	{
		ft_strdel(path);
		return ;
	}
	FT_INIT(char*, pwd, get_var(&g_shell, "PWD"));
	if (cas == -1)
	{
		if (file_name[0] != '/')
		{
			remove_last_dir(path, '/');
			tmp = *path;
			*path = ft_strjoin(*path, file_name);
			ft_strdel(&tmp);
		}
		else
			*path = file_name;
		tmp = *path;
		*path = path_converter(*path, home, pwd);
		ft_strdel(&tmp);
	}
	in_dir(*path, pwd);
	ft_strdel(path);
	free(pwd);
}

int					cd(char *line)
{
	FT_INIT(char**, tab_line, NULL);
	FT_INIT(int, len_tab, 0);
	if (!(tab_line = verif_args_cd(line, &len_tab)))
		return (1);
	FT_INIT(char*, pwd, get_var(&g_shell, "PWD"));
	FT_INIT(char*, home, get_var(&g_shell, "HOME"));
	FT_INIT(char*, option, NULL);
	FT_INIT(char*, sentence, NULL);
	FT_INIT(char*, path, NULL);
	FT_INIT(char*, file, NULL);
	set_option_sentence(&sentence, &option, len_tab, tab_line);
	path = len_tab == 1 ? ft_strdup(home) : path_converter(sentence, home, pwd);
	file = ft_strdup(path + (ft_strlen(path) -
		ft_strlen(ft_strrchr(path, '/')) + 1));
	len_tab = verif_access(&path, &file, option);
	go_to_dir(len_tab, &path, home, file);
	free_tab(tab_line);
	free(home);
	free(sentence);
	free(file);
	free(pwd);
	return (!len_tab ? 1 : 0);
}

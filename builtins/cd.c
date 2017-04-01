/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <dvirgile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/01 17:09:12 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

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

static int			set_option_sentence(char **sentence, char **option,
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
		{
			if (!(*sentence = get_var(g_shell.env, "OLDPWD")))
				return (0);
		}
		else
			*sentence = ft_strdup(tab_line[1]);
	}
	else if (len_tab == 1)
	{
		if (!(*sentence = get_var(g_shell.env, "HOME")))
			return (0);
	}
	else
		*sentence = ft_strdup("");
	return (1);
}

static void			in_dir(char **path, char *pwd)
{
	FT_INIT(char*, tmp, NULL);
	if (!(*path))
		return ;
	if (chdir((*path)))
		ft_putstr_fd("Error chdir\n", 2);
	else
	{
		if ((*path)[ft_strlen((*path)) - 1] == '/' && ft_strcmp(*path, "/"))
			(*path)[ft_strlen((*path)) - 1] = '\0';
		tmp = ft_strjoin("setenv PWD=", (*path));
		if ((*path))
		{
			free(g_shell.line);
			g_shell.line = ft_strdup((*path));
		}
		ft_setenv(tmp, DEFAULT);
		ft_strdel(&tmp);
		tmp = ft_strjoin("setenv OLDPWD=", pwd);
		ft_setenv(tmp, DEFAULT);
		ft_strdel(&tmp);
	}
	ft_strdel(&(*path));
}

static void			go_to_dir(int cas, char **path, char *home, char *file_name)
{
	FT_INIT(char*, tmp, NULL);
	if (!cas || !path || !file_name)
	{
		free(g_shell.line);
		g_shell.line = ft_strdup(*path);
		ft_strdel(path);
		return ;
	}
	FT_INIT(char*, pwd, getcwd(NULL, 1024));
	if (cas == -1)
	{
		if (file_name[0] != '/')
		{
			remove_last_dir(path, '/');
			tmp = *path;
			*path = ft_strjoin(*path, file_name);
			ft_strdel(&tmp);
		}
		*path = file_name[0] == '/' ? file_name : *path;
		tmp = *path;
		*path = path_converter(*path, home, pwd);
		ft_strdel(&tmp);
	}
	in_dir(&(*path), pwd);
	free(pwd ? pwd : NULL);
}

int					cd(char *line)
{
	FT_INIT(char**, tab_line, NULL);
	FT_INIT(int, len_tab, 0);
	if (!(tab_line = verif_args_cd(line, &len_tab)))
		return (0);
	FT_INIT(char*, pwd, getcwd(NULL, 1024));
	FT_INIT(char*, home, get_var(g_shell.env, "HOME"));
	FT_INIT(char*, option, NULL);
	FT_INIT(char*, sentence, NULL);
	FT_INIT(char*, path, NULL);
	FT_INIT(char*, file, NULL);
	if (!(set_option_sentence(&sentence, &option, len_tab, tab_line)))
	{
		free_tab(tab_line);
		free_cd_vars(&home, &sentence, &file, &pwd);
		return (error_cd("env", "Env variables HOME or OLDPWD not found"));
	}
	path = len_tab == 1 ? ft_strdup(home) : path_converter(sentence, home, pwd);
	if (path)
	{
		cd_suite(&file, &path, option, &len_tab);
		go_to_dir(len_tab, &path, home, file);
	}
	free_tab(tab_line);
	free_cd_vars(&home, &sentence, &file, &pwd);
	return (!len_tab ? 0 : 1);
}

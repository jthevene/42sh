/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 11:29:38 by dvirgile          #+#    #+#             */
/*   Updated: 2016/09/05 17:28:56 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

static char 		**verif_args_cd(char *line, int *len_tab)
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
		ft_putendl("cd: error arguments");
		ft_putendl("Try cd [-L|-P] [dir]");
		ft_putendl("Options:");
        ft_putendl("-L	force symbolic links to be followed");
        ft_putstr("-P	use the physical directory structure ");
        ft_putendl("without following symbolic");
    	ft_putendl("links");
	}
	if ((*len_tab) > 3)
		ft_putendl("cd: too many arguments");
	return (tab_line);
}

static void 		set_option_sentence(char **sentence, char **option, int len_tab, char **tab_line)
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

static void 		in_dir(char *path, char *pwd)
{
	FT_INIT(char*, tmp, NULL);
	if (chdir(path))
		ft_putstr("Error chdir\n");
	else
	{
		tmp = ft_strjoin("setenv PWD=", path);
		_42sh_setenv(tmp);
		ft_strdel(&tmp);
		tmp = ft_strjoin("setenv OLDPWD=", pwd);
		_42sh_setenv(tmp);
		ft_strdel(&tmp);
	}
}

static void 		go_to_dir(int cas, char *path, char *home, char *file_name)
{
	FT_INIT(char*, tmp, NULL);
	FT_INIT(char*, pwd, get_var(&g_shell, "PWD"));
	if (!cas)
		return ;
	if (cas == -1)
	{
		if (file_name[0] != '/')
		{
			remove_last_dir(&path, '/');
			tmp = path;
			path = ft_strjoin(path, file_name);
			ft_strdel(&tmp);
		}
		else
			path = file_name;
		path = path_converter(path, home, pwd);
		ft_strdel(&file_name);
	}
	in_dir(path, pwd);
}

int 		cd(char *line)
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
	path = len_tab == 1 ? home : path_converter(sentence, home, pwd);
	file = ft_strdup(path + (ft_strlen(path) - 
		ft_strlen(ft_strrchr(path, '/')) + 1));
	len_tab = verif_access(&path, &file, option);
	go_to_dir(len_tab, path, home, file);
	free(path);
	free(home);
	free(file);
	if (!len_tab)
		return (1);
	return (0);
}








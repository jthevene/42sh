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

#include "../code_dieuson/includes/42sh.h"

int			error_cd(char *type, char *file)
{
	ft_putstr("cd: ");
	ft_putstr(type);
	ft_putstr(": ");
	ft_putendl(file);
	return (0);
}

char		**lsh_read_line(char *line)
{
	char **commands;

	commands = NULL;
	if (!line)
		return (NULL);
	if (ft_strchr(line, ' '))
		commands = ft_strsplit(line, ' ');
	else
	{
		commands = (char**)malloc(sizeof(char*) * 2);
		commands[0] = ft_strdup(line);
		commands[1] = NULL;
	}
	return (commands);
}

int			verif_access(char *path, char *file)
{
	struct stat infos;

	lstat(path, &infos);
	if (access(path, F_OK) != 0)
		return (error_cd("no such file or directory", file));
	else if (access(path, X_OK) != 0 || !S_ISDIR(infos.st_mode))
		return (error_cd("permission denied", file));
	else if (!S_ISDIR(infos.st_mode))
		return (error_cd("not a directory", file));
	return (1);
}

char 		**verif_args_cd(char *line, int *len_tab)
{
	FT_INIT(char**, tab_line, lsh_read_line(line));
	while (tab_line && tab_line[*len_tab])
		(*len_tab)++;
	if (ft_strcmp(tab_line[0], "cd") || (*len_tab) > 3)
	{
		free_auto_tab(tab_line);
		tab_line = NULL;
	}
	if (tab_line && *len_tab == 3 && (ft_strcmp(tab_line[1], "-L") || ft_strcmp(tab_line[1], "-L")))
	{
		ft_putendl("cd: error arguments");
		ft_putendl("Try cd [-L|-P] [dir]");
		ft_putendl("Options:");
        ft_putendl("-L	force symbolic links to be followed");
        ft_putendl("-P	use the physical directory structure without following symbolic");
    	ft_putendl("links");
	}
	if ((*len_tab) > 3)
		ft_putendl("cd: too many arguments");
	return (tab_line);
}

void 		set_option_sentence(char **sentence, char **option, int len_tab, char **tab_line)
{
	if (len_tab == 3)
	{
		*option = tab_line[1];
		*sentence = ft_strdup(tab_line[2]);
	}
	else if (len_tab == 2)
		*sentence = ft_strdup(tab_line[1]);
	else
		*sentence = ft_strdup("");
}

void 		cd(char *line)
{
	FT_INIT(char**, tab_line, NULL);
	FT_INIT(int, len_tab, 0);
	if (!(tab_line = verif_args_cd(line, &len_tab)))
		return ;
	FT_INIT(char*, pwd, getcwd(NULL, 1024));
	FT_INIT(char*, old_pwd, getenv("OLDPWD"));
	FT_INIT(char*, home, getenv("HOME"));
	FT_INIT(char*, option, NULL);
	FT_INIT(char*, sentence, NULL);
	FT_INIT(char*, path, NULL);
	FT_INIT(char*, file, NULL);
	set_option_sentence(&sentence, &option, len_tab, tab_line);
	path = len_tab == 1 ? home : path_converter(sentence, home, pwd);
	file = ft_strdup(path + (ft_strlen(path) - ft_strlen(ft_strrchr(path, '/')) + 1));
	printf("1path =%s, file =%s, pwd =%s, len_tab =%d\n", path, file, getcwd(NULL, 1024), len_tab);
	if (verif_access(path, file))
		if (chdir(path))
			ft_putstr("Error chdir\n");
	printf("2path =%s, file =%s, pwd =%s,\n", path, file, getcwd(NULL, 1024));
//	printf("sentence =%s, option =%s, len_tab =%d, path =%s\n", sentence, option, len_tab, path);
	if (old_pwd || home || pwd || path || file)
		return ;
}









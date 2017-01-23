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

int			shell_cd(char **commands, char *pwd, char *old_pwd, char *home)
{
//	FT_INIT(char*, dir_dest, NULL);
//	FT_INIT(char*, dir, NULL);
	if (!commands)
		return (0);

//	dir_dest = set_dir_dest(commands, data->env);

//	chdir(dir_dest);
//	ft_strdel(&dir_dest);
//	free(dir);
	if (pwd || old_pwd || home)
		return (1);
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
//	printf("1sentence =%s,\n", *sentence);
}

static	char		*set_begining(char *sentence, char *home,
					char *current_path)
{
	FT_INIT(char*, new_path, ft_strnew(ft_strlen(sentence) + 100));
	if (ft_strlen(sentence) && !ft_strcmp(sentence, "."))
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

static void			remove_last_dir(char **str, char c)
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

char 		*convert_path(char *sentence, char *home, char *pwd)
{
	FT_INIT(int, i, 0);
	FT_INIT(char*, str, NULL);
	FT_INIT(char**, path_tab, NULL);
	if (sentence[0] != '/')
		str	= set_begining(sentence, home, pwd);
	path_tab = ft_strsplit(str ? str : sentence, '/');
	ft_strdel(&str);
	str = ft_strnew(ft_strlen(sentence));
	str[0] = '/';
	while (path_tab && path_tab[i])
	{
		ft_printf("str =%s,\n", str);
		printf("path[%d] =%s,\n", i, path_tab[i]);
		if (!ft_strcmp(path_tab[i], "~"))
			ft_strcat(str, home);
		else if (!ft_strcmp(path_tab[i], ".."))
		{
//			ft_putstr("remove slash\n");
			printf("str1 =%s,\n", str);
			remove_last_dir(&str, '/');
			printf("str2 =%s,\n", str);
			printf("str3 =%s,\n", str);
		}
		else if (!ft_strcmp(path_tab[i], "."))
			;
		else
		{
			ft_strcat(str, path_tab[i]);
			if ((path_tab[i + 1] && str[ft_strlen(str) - 1] != '/'))
				ft_strcat(str, "/");
		}
		i++;
	}
	ft_printf("str =%s,\n", str);
//	free_auto_tab(path_tab);
	return (str);
}

void 		cd(char *line)
{
	FT_INIT(char**, tab_line, NULL);
	FT_INIT(int, len_tab, 0);
	if (!(tab_line = verif_args_cd(line, &len_tab)))
		return ;
	FT_INIT(char*, pwd, getenv("PWD"));
	FT_INIT(char*, old_pwd, getenv("OLDPWD"));
	FT_INIT(char*, home, getenv("HOME"));
	FT_INIT(char*, option, NULL);
	FT_INIT(char*, sentence, NULL);
	FT_INIT(char*, path, NULL);
//	FT_INIT(char**, dirs, NULL);
	set_option_sentence(&sentence, &option, len_tab, tab_line);
//	dirs = ft_strsplit(sentence, '/');
//	default_sentence(&sentence);
	path = convert_path(sentence, home, pwd);
//	printf("sentence =%s, option =%s, len_tab =%d, path =%s\n", sentence, option, len_tab, path);
	if (old_pwd || home || pwd || path)
		return ;
}









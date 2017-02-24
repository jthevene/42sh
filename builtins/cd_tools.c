/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:36:55 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void		free_cd_vars(char **home, char **sentence, char **file, char **pwd)
{
	free((*home));
	free((*sentence));
	free((*file));
	free((*pwd));
}

int			error_cd(char *type, char *file)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd("\n", 2);
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

int			verif_access(char **path, char **file, char *option)
{
	struct stat infos;
	ssize_t		r;

	FT_INIT(char*, link_name, NULL);
	lstat(*path, &infos);
	if (access(*path, F_OK) != 0)
		return (error_cd("no such file or directory", *file));
	else if (S_ISLNK(infos.st_mode) && !ft_strcmp(option, "-P"))
	{
		link_name = ft_strnew(infos.st_size + 1);
		r = readlink(*path, link_name, infos.st_size + 1);
		link_name[r] = '\0';
		ft_strdel(file);
		*file = link_name;
		return (-1);
	}
	else if (!S_ISDIR(infos.st_mode) && !S_ISLNK(infos.st_mode))
		return (error_cd("not a directory", *file));
	else if (access(*path, X_OK) != 0)
		return (error_cd("permission denied", *file));
	return (1);
}

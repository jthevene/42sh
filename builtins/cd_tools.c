/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 16:47:28 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/13 12:38:58 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

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

int			verif_access(char **path, char **file, char *option)
{
	struct stat infos;
	ssize_t		r;

	FT_INIT(char*, link_name, NULL);
	lstat(*path, &infos);
	if (access(*path, F_OK) != 0)
		return (error_cd("no such file or directory", *file));
	else if (access(*path, X_OK) != 0)
		return (error_cd("permission denied", *file));
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
	return (1);
}

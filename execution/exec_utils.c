/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 08:20:31 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/22 08:57:51 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int			verif_access_bin(char *path)
{
	struct stat infos;

	lstat(path, &infos);
	if (access(path, F_OK) != 0)
		return (0);
	return (1);
}

int			verif_access_others(char *path)
{
	struct stat infos;

	lstat(path, &infos);
	if (access(path, F_OK) != 0)
		return (0);
	else if (access(path, X_OK) != 0 || !S_ISDIR(infos.st_mode))
		return (0);
	else if (!S_ISDIR(infos.st_mode))
		return (0);
	return (1);
}

char		**get_bin_directories(void)
{
	FT_INIT(char **, bin_directories, NULL);
	FT_INIT(char*, tmp, NULL);
	if (!g_shell.env)
		return (NULL);
	tmp = get_var(&g_shell, "PATH");
	if (!tmp)
		return (NULL);
	else
	{
		bin_directories = ft_strsplit(tmp, ':');
		free(tmp);
	}
	return (bin_directories);
}

char		**get_args(char *content)
{
	FT_INIT(char **, args, NULL);
	if (!content)
		return (NULL);
	if (ft_strchr(content, ' '))
		args = ft_strsplit(content, ' ');
	else
	{
		args = (char **)malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(content);
		args[1] = NULL;
	}
	return (args);
}

void		error_exec(char **args, char **cmd)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_strdel(&(*cmd));
}

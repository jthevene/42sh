/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/13 17:21:46 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

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
	tmp = get_var(g_shell.env, "PATH");
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

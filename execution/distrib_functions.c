/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distrib_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 17:29:42 by dvirgile          #+#    #+#             */
/*   Updated: 2017/02/07 10:57:31 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

int		detect_builtins(char* to_exec, char *command_line)
{
	if (!ft_strcmp(to_exec, "echo"))
		return (_42sh_echo(to_exec));
	else if (!ft_strcmp(to_exec, "unsetenv"))
		return (_42sh_unsetenv(to_exec));
	else if (!ft_strcmp(to_exec, "setenv"))
		return (_42sh_setenv(to_exec));
	else if (!ft_strcmp(to_exec, "env"))
		return (_42sh_env());
	else if (!ft_strcmp(to_exec, "cd"))
		return (cd(command_line));
	else if (!ft_strcmp(to_exec, "history"))
		return (history_hub(command_line));
	else if (!ft_strcmp(to_exec, "exit"))
		ft_exit();
	return (-1);
}

static int			verif_access_bin_directory(char *path)
{
	struct stat infos;

	if (lstat(path, &infos) == -1)
		return (0);
	if (access(path, F_OK) != 0)
		return (0);
	else if (access(path, X_OK) != 0 || !S_ISDIR(infos.st_mode))
		return (0);
	else if (!S_ISDIR(infos.st_mode))
		return (0);
	return (1);
}

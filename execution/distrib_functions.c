/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distrib_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 17:29:42 by dvirgile          #+#    #+#             */
/*   Updated: 2017/02/13 12:38:40 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

static int 	verif_buitins(char *to_exec)
{
	if (!ft_strcmp(to_exec, "echo"))
		return (1);
	else if (!ft_strcmp(to_exec, "unsetenv"))
		return (1);
	else if (!ft_strcmp(to_exec, "setenv"))
		return (1);
	else if (!ft_strcmp(to_exec, "env"))
		return (1);
	else if (!ft_strcmp(to_exec, "cd"))
		return (1);
	else if (!ft_strcmp(to_exec, "history"))
		return (1);
	else if (!ft_strcmp(to_exec, "exit"))
		return (1);
	return (0);
}

int			detect_builtins(char *to_exec, char *command_line)
{
	if (verif_buitins(to_exec))
		handle_redirections();
	if (!ft_strcmp(to_exec, "echo"))
		return (ft_echo(command_line));
	else if (!ft_strcmp(to_exec, "unsetenv"))
		return (ft_unsetenv(command_line));
	else if (!ft_strcmp(to_exec, "setenv"))
		return (ft_setenv(command_line));
	else if (!ft_strcmp(to_exec, "env"))
		return (ft_env(command_line));
	else if (!ft_strcmp(to_exec, "cd"))
		return (cd(command_line));
	else if (!ft_strcmp(to_exec, "history"))
		return (history_hub(command_line));
	else if (!ft_strcmp(to_exec, "exit"))
		ft_exit();
	return (-1);
}

int			verif_access_bin_directory_(char *path)
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

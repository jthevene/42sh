/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distrib_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 17:29:42 by dvirgile          #+#    #+#             */
/*   Updated: 2017/01/30 17:29:43 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

int		detect_builtins(char* command)
{
	if (!ft_strcmp(command, "echo"))
		_42sh_echo(command);
	else if (!ft_strcmp(command, "unsetenv"))
		_42sh_unsetenv(command);
	else if (!ft_strcmp(command, "setenv"))
		_42sh_setenv(command);
	else if (!ft_strcmp(command, "env"))
		_42sh_env();
	else if (!ft_strcmp(command, "cd"))
		cd(g_shell.line);
	else
		return (0);
	return (1);
}

int			verif_access_bin_directory(char *path)
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


char		**get_bin_directories(char **env_tab)
{
	FT_INIT(char**, bin_directories, NULL);
	FT_INIT(char*, tmp, NULL);
	FT_INIT(int, i, 0);
	if (!env_tab)
		return (NULL);
	while (env_tab && env_tab[i])
	{
		if (env_tab && !ft_strncmp(env_tab[i], "PATH=", 5))
		{
			tmp = ft_strchr(env_tab[i], '=') + 1;
			if (tmp)
				bin_directories = ft_strsplit(tmp, ':');
			break ;
		}
		i++;
	}
	return (bin_directories);
}




int			_42sh_launch(char **args, char **env, char *command)
{
	FT_INIT(char**, bin_directories, NULL);
	FT_INIT(char*, cmd, NULL);
	FT_INIT(char*, tmp, NULL);
	FT_INIT(int, i, 0);
	if (!args)
		return (0);
	bin_directories = get_bin_directories(env);
	while (bin_directories && bin_directories[i])
	{
		if (verif_access_bin_directory(bin_directories[i]))
		{
			cmd = ft_strjoin(bin_directories[i], "/");
			tmp = cmd;
			cmd = ft_strjoin(cmd, command);
			ft_strdel(&tmp);
			if (execve(cmd, args, env) != -1)
			{
				ft_strdel(&cmd);
				return (1);
			}
			ft_strdel(&cmd);
		}
		i++;
	}
	if (!ft_strcmp(args[0], "exit"))
	{
		go_to_end();
		ft_putstr("\n");
		ft_reset_termios(g_shell.t_back);
		exit(0);
	}
	ft_printf("42sh: command not found: %s\n", args[0]);
	return (0);
}

void 	distrib_functions()
{
	FT_INIT(char**, args, ft_strsplit(g_shell.line, ' '));
	if (detect_builtins(args[0]))
		return free_auto_tab(args);
	FT_INIT(int, pid, 0);
	FT_INIT(char**, env, lst_to_tab(g_shell.env));
	FT_INIT(char*, command, args[0]);
	pid = fork();
	if (pid == 0)
	{
		_42sh_launch(args, env, command);
		exit(0);
	}
	wait(&pid);
}





















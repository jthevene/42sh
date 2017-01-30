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

int		detect_builtins(void)
{
	if (ft_strstr(g_shell.line, "echo"))
		_42sh_echo(g_shell.line);
	else if (ft_strstr(g_shell.line, "unsetenv "))
		_42sh_unsetenv(g_shell.line);
	else if (ft_strstr(g_shell.line, "setenv "))
		_42sh_setenv(g_shell.line);
	else if (ft_strstr(g_shell.line, "env "))
		_42sh_env();
	else if (ft_strstr(g_shell.line, "cd "))
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


char		**get_bin_directories(t_var *env)
{
	FT_INIT(char**, bin_directories, NULL);
	if (!envp)
		return (NULL);
	while (envp && envp[i])
	{
		if (envp && !ft_strncmp(envp[i], "PATH=", 5))
		{
			tmp = ft_strchr(envp[i], '=') + 1;
			if (tmp)
				bin_directories = ft_strsplit(tmp, ':');
			break ;
		}
		i++;
	}
	return (bin_directories);
}



int			_42sh_launch(char **args, t_sh *data, int i)
{
	FT_INIT(char*, bin_directories, NULL);
	FT_INIT(char*, cmd, NULL);
	FT_INIT(char*, tmp, NULL);
	if (!args)
		return (0);
	bin_directories = get_bin_directories(g_shell.env);
	while (bin_directories && bin_directories[i])
	{
		if (verif_access_others(bin_directories[i]))
		{
			cmd = ft_strjoin(bin_directories[i], "/");
			tmp = cmd;
			cmd = ft_strjoin(cmd, args[0]);
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
	ft_putstr("minishell: command not found: ");
	ft_putendl(args[0]);
	return (0);
}

void 	distrib_functions()
{
	if (detect_builtins)
		return ;
	FT_INIT(int, pid, 0);
	FT_INIT(int, commands, g_shell.line);
	pid = fork();
	if (pid == 0)
	{
		_42sh_launch(commands, data, 0);
		exit(0);
	}






	FT_INIT(char*, line, NULL);
	FT_INIT(char**, commands, NULL);
	while (1)
	{
		ret = get_next_line(0, &line);
		if (ret && ft_strlen(line))
		{
			commands = lsh_read_line(line);
			free(line);
			if (verif_implements(commands[0], data))
				distrib_functions(commands, data);
			else
			{
				pid = fork();
				if (pid == 0)
				{
					lsh_launch(commands, data, 0);
					exit(0);
				}
			}
			free_simple_tab(&commands);
		}
		wait(&pid);
		ft_putstr("\n$> ");
	}
}
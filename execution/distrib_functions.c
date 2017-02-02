/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distrib_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 17:29:42 by dvirgile          #+#    #+#             */
/*   Updated: 2017/02/02 10:46:55 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

static int		detect_builtins(char* to_exec, char *command_line)
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
		history_hub(command_line);
	else if (!ft_strcmp(to_exec, "exit"))
		ft_exit();
	else
		return (0);
	return (1);
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


static char		**get_bin_directories(char **env_tab)
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

static int			_42sh_launch(char **args, char **env, char *command)
{
	FT_INIT(char**, bin_directories, NULL);
	FT_INIT(char*, cmd, NULL);
	FT_INIT(char*, tmp, NULL);
	FT_INIT(int, i, 0);
	if (command[0] == '/' && !access(command, F_OK) && !access(command, X_OK)
		&& (execve(command, args, env) != -1))
		return (1);
	else
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
	ft_printf("42sh: command not found: %s\n", args[0]);
	return (0);
}

void 	distrib_functions(char *command_line)
{
	int descripteurTube[2];
	int descripteurError[2];
	char *buff;

	buff = ft_strnew(1024);


	FT_INIT(char**, args, ft_strsplit(command_line, ' '));
	FT_INIT(int, result, 0);
	if ((result = detect_builtins(args[0], command_line)))
	{
		g_shell.result_exec = result;
		return (free_auto_tab(args));
	}
	FT_INIT(int, pid, 0);
//	FT_INIT(int, pid2, 0);
	FT_INIT(char**, env, lst_to_tab(g_shell.env));
	FT_INIT(char*, command, args[0]);
//	ft_putstr("lol");
	if (pipe(descripteurTube) != 0)
		return ;
	if (pipe(descripteurError) != 0)
		return ;
	pid = fork();
	if (pid == 0 && args)
	{
		close(descripteurTube[0]);
		descripteurTube[1] = dup(1);
//		dup2(descripteurTube[1], dup(1));

		close(descripteurError[0]);
		descripteurError[1] = dup(2);
//		dup2(descripteurError[1], dup(2));
//		if (buff)
//			buff = "fd";

//		pid2 = fork();
//		if (pid2 == 0)
//		{
			_42sh_launch(args, env, command);
//			exit(0);
//		}
//		else if (!read(1, buff, 1024))
//			ft_putstr("toot");
//		read(descripteurTube[1], buff, 1024);
//		printf("Message envoyer =%s,\n", buff);
		exit(0);
	}
	else
	{
//		FT_INIT(char* ,message_fils, ft_strdup("HELLO EVERY"));
		close(descripteurTube[1]);
		FT_INIT(int, len_STDOUT, read(descripteurTube[0], buff, 1024));
		ft_printf(buff);
		ft_strdel(&buff);
		buff = ft_strnew(1024);
		close(descripteurError[1]);
		FT_INIT(int, len_ERROR, read(descripteurError[0], buff, 1024));
		if (len_ERROR && !len_STDOUT)
			ft_printf(buff);
		g_shell.result_exec = len_STDOUT ? 1 : 0;
//		ft_printf("len_stdout =%d, len_error =%d,\n", len_STDOUT, len_ERROR);
//		ft_printf("g_shell.result_exec =%d,\n", g_shell.result_exec);	
	}
	wait(&pid);
//	ft_putchar('\n');
}

/*
void 	distrib_functions(char *command_line)
{
	int descripteurTube[2];
	char *buff;

	buff = ft_strnew(1024);


	FT_INIT(char**, args, ft_strsplit(command_line, ' '));
	FT_INIT(int, result, 0);
	if ((result = detect_builtins(args[0], command_line)))
	{
		g_shell.result_exec = result;
		return (free_auto_tab(args));
	}
	FT_INIT(int, pid, 0);
	FT_INIT(char**, env, lst_to_tab(g_shell.env));
	FT_INIT(char*, command, args[0]);
	ft_putstr("lol");
//	dup2(descripteurTube[1], STDOUT_FILENO);
	pipe(descripteurTube);
	pid = fork();
	if (pid == 0 && args)
	{
		close(descripteurTube[1]);
//		if (buff)
//			buff = "fd";
		read(descripteurTube[0], buff, 1024);
		printf("Message recu =%s,\n", buff);
		_42sh_launch(args, env, command);
		exit(0);
	}
	else
	{
		close(descripteurTube[0]);
		FT_INIT(char* ,message_fils, ft_strdup("HELLO EVERY"));
		write(descripteurTube[1], message_fils, 1024);
		printf("Message envoyer au pere=%s,\n", message_fils);
	}
	wait(&pid);
//	ft_putchar('\n');
}
*/

/*
void 	distrib_functions(char *command_line)
{
	FT_INIT(char**, args, ft_strsplit(command_line, ' '));
	FT_INIT(int, result, 0);
	if ((result = detect_builtins(args[0], command_line)))
	{
		g_shell.result_exec = result;
		return (free_auto_tab(args));
	}
	FT_INIT(int, pid, 0);
	FT_INIT(char**, env, lst_to_tab(g_shell.env));
	FT_INIT(char*, command, args[0]);
	pid = fork();
	if (pid == 0 && args)
	{
		_42sh_launch(args, env, command);
		exit(0);
	}
	wait(&pid);
//	ft_putchar('\n');
}
*/





















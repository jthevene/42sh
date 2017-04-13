/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/13 10:41:26 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

int				exec_function_execve(char *cmd, char **args)
{
	FT_INIT(char **, env_tab, lst_to_tab(g_shell.env));
	handle_redirections(IS_NOT_BUILTIN);
	if (execve(cmd, args, g_shell.env_opt == FALSE ? env_tab : NULL) == -1)
	{
		free_tab(env_tab);
		return (0);
	}
	else
	{
		free_tab(env_tab);
		return (1);
	}
}

int				parse_bin_directories(char **bin_dir, char **args)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, cmd, NULL);
	FT_INIT(char *, tmp, NULL);
	if (args[0][0] == '/' || !ft_strncmp(args[0], "./", 2))
	{
		if (verif_access_bin(args[0]))
			exec_function_execve(args[0], args);
		else
			return (error_parse_bin(args[0]));
	}
	while (bin_dir && bin_dir[i])
	{
		if (verif_access_others(bin_dir[i]))
		{
			cmd = ft_strjoin(bin_dir[i], "/");
			tmp = cmd;
			cmd = ft_strjoin(tmp, args[0]);
			ft_strdel(&tmp);
			if (verif_access_bin(cmd))
				exec_function_execve(cmd, args);
			ft_strdel(&cmd);
		}
		i++;
	}
	return (error_exec(args, &cmd));
}

static void		exec_function2(pid_t pid, int *return_value)
{
	wait(&pid);
	init_termios(g_shell.t_back);
	if (WEXITSTATUS(pid) == 0)
		(*return_value) = 1;
	else
		(*return_value) = 0;
	restablish_fd(&g_shell.save_list);
}

static void		set_default_shell(void)
{
	g_shell.t_back.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, 0, &(g_shell.t_back));
}

int				exec_function(char **content)
{
	FT_INIT(pid_t, pid, 0);
	if (!call_redirections(content))
		return (0);
	FT_INIT(char **, bin_dir, get_bin_directories());
	FT_INIT(char **, args, get_args((*content)));
	FT_INIT(int, return_value, 0);
	FT_INIT(int, return_builtins, 0);
	if ((return_builtins = detect_builtins(args[0], (*content))) != -1)
	{
		free_tab(bin_dir);
		free_tab(args);
		return (return_builtins);
	}
	if ((pid = fork()) == -1)
		return (0);
	else
		set_default_shell();
	if (pid == 0)
		exit(parse_bin_directories(bin_dir, args));
	else
		exec_function2(pid, &return_value);
	free_tab(bin_dir);
	free_tab(args);
	return (return_value);
}

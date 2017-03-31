/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/23 15:27:47 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

static int		execve_pipe(char **content)
{
	call_redirections(content);
	FT_INIT(char **, bin_dir, get_bin_directories());
	FT_INIT(char **, args, get_args((*content)));
	FT_INIT(int, return_builtins, 0);
	if ((return_builtins = detect_builtins(args[0], (*content)) != -1))
		exit(return_builtins);
	return (parse_bin_directories(bin_dir, args));
}

char			**content_to_exec(t_tree *left, t_tree *right)
{
	if (!ft_strcmp(right->content, "|") && left)
	{
		if (right->left && right->right)
			exit(exec_pipe(right->left, right->right));
	}
	return (&right->content);
}

static int		error_fork(int fd[2])
{
	close(fd[0]);
	close(fd[1]);
	return (0);
}

int				exec_pipe(t_tree *left, t_tree *right)
{
	int			fd[2];

	FT_INIT(pid_t, pid, 0);
	FT_INIT(int, ret1, 0);
	FT_INIT(int, ret2, 0);
	if (pipe(fd) == -1)
		return (0);
	if ((pid = fork()) == -1)
		return (error_fork(fd));
	if ((int)pid == 0)
	{
		call_redirections(&left->content);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		exit(execve_pipe(&left->content));
	}
	call_redirections(&right->content);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	ret1 = WEXITSTATUS(pid) == 0 ? 1 : 0;
	ret2 = execve_pipe(content_to_exec(left, right));
	wait(&pid);
	return (!ret1 || !ret2 ? 0 : 1);
}

int				run_pipe(t_tree *left, t_tree *right)
{
	FT_INIT(pid_t, pid, 0);
	FT_INIT(int, ret, 0);
	pid = fork();
	if ((int)pid == -1)
		ret = 0;
	else if ((int)pid == 0)
	{
		g_shell.t_back.c_lflag |= (ICANON | ECHO);
		tcsetattr(0, 0, &(g_shell.t_back));
		exit(ret = exec_pipe(left, right));
	}
	wait(NULL);
	init_termios(g_shell.t_back);
	restablish_fd(&g_shell.save_list);
	return (ret);
}

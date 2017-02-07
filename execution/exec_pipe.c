/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 09:28:00 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/07 09:28:01 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

static int		execve_pipe(char *content)
{
	FT_INIT(char **, bin_dir, get_bin_directories());
	FT_INIT(char **, args, get_args(content));
	return (parse_bin_directories(bin_dir, args));
}

int				exec_pipe(t_tree *left, t_tree *right)
{
	FT_INIT(pid_t, pid, 0);
	FT_INIT(int, fd[2], {0});
	FT_INIT(int, ret1, 0);
	FT_INIT(int, ret2, 0);
	if (!pipe(fd))
		return (0);
	if ((pid = fork()) == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		execve_pipe(left->content);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	wait(&pid);
	ret1 = WEXITSTATUS(pid) == 0 ? 1 : 0;
	if (!ret1)
		return (0);
	ret2 = execve_pipe(right->content);
	return (ret1 & ret2);
}

int				run_pipe(t_tree *left, t_tree *right)
{
	FT_INIT(pid_t, pid, 0);
	FT_INIT(int, ret, 0);
	if ((pid = fork()) == 0)
		ret = exec_pipe(left, right);
	else
		ret = 0;
	wait(NULL);
	return (ret);
}

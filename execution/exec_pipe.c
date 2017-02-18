/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 09:28:00 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/13 12:38:38 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

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

char 			**content_to_exec(t_tree *left, t_tree *right)
{
//	FT_INIT(char *, content, right->content);
	if (!ft_strcmp(right->content, "|") && left)
	{
		if (right->left && right->right)
			exit(exec_pipe(right->left, right->right));
	}
	return (&right->content);
}


int				exec_pipe(t_tree *left, t_tree *right)
{
	int			fd[2];

	if (right->type == PIPE)
	{
//		printf("right->content = %s, right->left->content = %s, right->right->content = %s\n", right->content, right->left->content, right->right->content);
//		ft_exit();
	}
	FT_INIT(pid_t, pid, 0);
	FT_INIT(int, ret1, 0);
	FT_INIT(int, ret2, 0);
	if (pipe(fd) == -1)
		return (0);
	if ((pid = fork()) == -1)
	{
		close(fd[0]);
		close(fd[1]);
	}
	if ((int)pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		exit(execve_pipe(&left->content));
	}
	wait(&pid);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	ret1 = WEXITSTATUS(pid) == 0 ? 1 : 0;
	ret2 = execve_pipe(content_to_exec(left, right));
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
		exit(ret = exec_pipe(left, right));
	wait(NULL);
	return (ret);
}

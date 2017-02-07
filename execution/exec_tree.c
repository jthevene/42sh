/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:55:32 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/04 12:22:46 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

int				exec_function_execve(char *cmd, char **args)
{
	FT_INIT(char **, env_tab, lst_to_tab(g_shell.env));
	printf("about to execve\n");
	if (execve(cmd, args, env_tab) == -1)
	{
		printf("didn't work\n");
		free_tab(env_tab);
		ft_strdel(&cmd);
		return (0);
	}
	else
	{
		printf("worked\n");
		free_tab(env_tab);
		ft_strdel(&cmd);
		return (1);
	}
}

int 			parse_bin_directories(char **bin_dir, char **args)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, cmd, NULL);
	FT_INIT(char *, tmp, NULL);
	while (bin_dir && bin_dir[i])
	{
		printf("parsing_bin_dir\n");
		if (verif_access_others(bin_dir[i]))
		{
			cmd = ft_strjoin(bin_dir[i], "/");
			tmp = cmd;
			cmd = ft_strjoin(cmd, args[0]);
			ft_strdel(&tmp);
			printf("found bin_dir\n");
			return (exec_function_execve(cmd, args));
		}
		i++;
	}
	return (0);
}

<<<<<<< HEAD
int			exec_function(char *content)
=======
static int		exec_function(char *content)
>>>>>>> 3a57e48b64baed2a2ed602b79fe575bb2d37189b
{
	pid_t		pid;

	FT_INIT(char **, bin_dir, get_bin_directories());
	FT_INIT(char **, args, get_args(content));
	FT_INIT(int, return_value, 0);
	if ((pid = fork()) == -1)
		return (0);
	if (pid == 0)
		exit(parse_bin_directories(bin_dir, args));
	else
	{
		wait(&pid);
		if (WEXITSTATUS(pid) == 0)
			return_value = 1;	
		else
			return_value = 0;
	}
	return (return_value);
}
<<<<<<< HEAD
int				exec_pipe(t_tree *left, t_tree *right)
{
	int			fd[2];
	pid_t		pid;

	ft_printf("EXECUTION PIPE GOO\n");
	if (pipe(fd) != 0)
		return (0);
	if (!left || !left->content || !right || !right->content 
		|| (pid = fork()) == -1)
		return (0);
	if (pid == 0)
	{
//		ft_putstr("EXECUTION left\n");
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (!exec_function(left->content))
		{
//			ft_putstr("ERROR PIPE LEFT\n");
			return (0);
		}
		exit(0);
	}
	else
	{
	//	dup2(STDOUT_FILENO, fd[1]);
//		wait(&pid);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
//		dup2(fd[0], STDIN_FILENO);
//		ft_putstr("EXECUTION right\n");
		if (!exec_function(right->content))
		{
//			ft_putstr("ERROR RIGHT\n");
	//		exit(0);
			return (0);

		}
	}
	wait(&pid);
	return (1);
}
=======
>>>>>>> 3a57e48b64baed2a2ed602b79fe575bb2d37189b

int				exec_tree(t_tree *tree)
{
	if (!tree)
		return (0);
	FT_INIT(int, test, 0);
	if (tree->type == SEMICOLON)
	{
		exec_tree(tree->left);
		exec_tree(tree->right);
	}
	else if (tree->type == AND)
	{
		if (exec_tree(tree->left))
			exec_tree(tree->right);
	}
	else if (tree->type == OR)
	{
		if (!exec_tree(tree->left))
			exec_tree(tree->right);
	}
	else if (tree->type == PIPE)
		return (run_pipe(tree->left, tree->right));
	else if (tree->left && tree->left->type != WORDS)
		exec_tree(tree->left);
	else if (tree->left && tree->left->type == WORDS)
		return (exec_function(tree->left->content));
	else if (tree->right && tree->right->type != WORDS)
		exec_tree(tree->right);
	else if (tree->right && tree->right->type == WORDS)
		return (exec_function(tree->right->content));
	else if (!tree->right && !tree->left && tree->content && tree->type == WORDS)
	{
		test = exec_function(tree->content);
		ft_printf("TREE CONTENT TEST =%d,\n", test);
		return (test);
	}
//		ft_printf("YOUPIIIIIIIIIIIII\n");
//	ft_printf("EXEC TREE RETURN bien 0 left =%s, type =%d\n", tree->content, tree->type);
	return (0);
}

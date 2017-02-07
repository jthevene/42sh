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
	FT_INIT(int, result, 0);
	if ((result = detect_builtins(args[0], cmd)))
		return (result);
	if (execve(cmd, args, env_tab) == -1)
	{
		free_tab(env_tab);
		ft_strdel(&cmd);
		return (0);
	}
	else
	{
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
		if (verif_access_others(bin_dir[i]))
		{
			cmd = ft_strjoin(bin_dir[i], "/");
			tmp = cmd;
			cmd = ft_strjoin(cmd, args[0]);
			ft_strdel(&tmp);
			exec_function_execve(cmd, args);
		}
		i++;
	}
	return (0);
}

int			exec_function(char *content)
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

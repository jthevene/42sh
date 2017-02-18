/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 15:55:32 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/17 18:49:50 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

int				exec_function_execve(char *cmd, char **args)
{
	FT_INIT(char **, env_tab, lst_to_tab(g_shell.env));
	handle_redirections();
	if (execve(cmd, args, g_shell.env_opt == FALSE ? env_tab : NULL) == -1)
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

int			verif_access_bin(char *path)
{
	struct stat infos;

	lstat(path, &infos);
	if (access(path, F_OK) != 0)
		return (0);
	return (1);
}

void			error_exec(char **args)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

int				parse_bin_directories(char **bin_dir, char **args)
{
	FT_INIT(int, i, 0);
	FT_INIT(char *, cmd, NULL);
	FT_INIT(char *, tmp, NULL);
	if (args[0][0] == '/')
	{
		if (verif_access_bin(args[0]))
			exec_function_execve(args[0], args);
		else
			return (ft_printf("21sh: %s: No such file or directory\n", args[0]));
	}
	while (bin_dir && bin_dir[i])
	{
		if (verif_access_others(bin_dir[i]))
		{
			cmd = ft_strjoin(bin_dir[i], "/");
			tmp = cmd;
			cmd = ft_strjoin(cmd, args[0]);
			ft_strdel(&tmp);
			if (verif_access_bin(cmd))
				exec_function_execve(cmd, args);
		}
		i++;
	}
	error_exec(args);
	return (0);
}

int				exec_function(char **content)
{
	FT_INIT(pid_t, pid, 0);
	FT_INIT(char *, tmp, hub_right_redir(ft_strdup((*content))));
	ft_strdel(&(*content));
	(*content) = ft_strdup(tmp);
	ft_strdel(&tmp);
	FT_INIT(char **, bin_dir, get_bin_directories());
	FT_INIT(char **, args, get_args((*content)));
	FT_INIT(int, return_value, 0);
	FT_INIT(int, return_builtins, 0);
	if ((return_builtins = detect_builtins(args[0], (*content)) != -1))
	{
		free_tab(bin_dir);
		free_tab(args);
		return (return_builtins);
	}
	if ((pid = fork()) == -1)
		return (0);
	else
	{
		g_shell.t_back.c_lflag |= (ICANON | ECHO);
		tcsetattr(0, 0, &(g_shell.t_back));
	}
	if (pid == 0)
		exit(parse_bin_directories(bin_dir, args));
	else
	{
		wait(&pid);
		init_termios(g_shell.t_back);
		if (WEXITSTATUS(pid) == 0)
			return_value = 1;
		else
			return_value = 0;
	}
	free_tab(bin_dir);
	free_tab(args);
	return (return_value);
}

static int		exec_tree2(t_tree *tree)
{
	if (tree->type == PIPE)
		return (run_pipe(tree->left, tree->right));
//	else if (tree->type == MORE || tree->type == DMORE)
//		return (run_redir(tree->left, tree->right, tree->type));
	else if (tree->type == LESS)
		return (simple_left(tree->left->content, tree->right->content));
	else if (tree->left && tree->left->type != WORDS)
		exec_tree(tree->left);
	else if (tree->left && tree->left->type == WORDS)
		return (exec_function(&tree->left->content));
	else if (tree->right && tree->right->type != WORDS)
		exec_tree(tree->right);
	else if (tree->right && tree->right->type == WORDS)
		return (exec_function(&tree->right->content));
	else if (!tree->right && !tree->left && tree->content
			&& tree->type == WORDS)
		return (exec_function(&tree->content));
	return (0);
}

int				exec_tree(t_tree *tree)
{
	if (!tree)
		return (0);
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
	else
		return (exec_tree2(tree));
	return (0);
}

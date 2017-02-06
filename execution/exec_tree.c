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

static int		exec_function_execve(char *cmd, char **args)
{
	FT_INIT(char **, env_tab, lst_to_tab(g_shell.env));
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

int				exec_function(char *content)
{
	pid_t		pid;
	int descripteurTube[2];
	int descripteurError[2];

	FT_INIT(char **, bin_dir, get_bin_directories());
	FT_INIT(char *, cmd, NULL);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char **, args, get_args(content));
	FT_INIT(int, i, 0);
	FT_INIT(char*, buff, ft_strnew(1024));

	if (pipe(descripteurTube) != 0)
		return (0);
	if (pipe(descripteurError) != 0)
		return (0);

	if ((pid = fork()) == -1)
		return (0);
	if (pid == 0 && args)
	{
		close(descripteurTube[0]);
		descripteurTube[1] = dup(1);

		close(descripteurError[0]);
		descripteurError[1] = dup(2);

		while (bin_dir && bin_dir[i])
		{
			if (verif_access_others(bin_dir[i]))
			{
				cmd = ft_strjoin(bin_dir[i], "/");
				tmp = cmd;
				cmd = ft_strjoin(cmd, args[0]);
				ft_strdel(&tmp);
				printf("GO EXECVE\n");
				if (exec_function_execve(cmd, args))
					exit(0);
			}
			i++;
		} //METTRE ICI LA GESTION D'ERREUR COMMAND NOT FOUND
	}
	else
	{
		close(descripteurTube[1]);
		FT_INIT(int, len_STDOUT, read(descripteurTube[0], buff, 1024));
		ft_printf("buf =%s,\n", buff);
		ft_bzero(&buff, ft_strlen(buff));
		close(descripteurError[1]);
		FT_INIT(int, len_ERROR, read(descripteurError[0], buff, 1024));
		if (len_ERROR)
			return (0);
		else if (len_STDOUT)
			return (1);
	}

	wait(&pid);
	return (0);
}

int				exec_pipe(t_tree *left, t_tree *right)
{
	int			fd[2];
	pid_t		pid;

	if (pipe(fd) != 0)
		return (0);
	if (!left || !left->content || !right || !right->content 
		|| (pid = fork()) == -1)
		return (0);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
	if (!exec_function(left->content))
		return (0);
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	if (!exec_function(right->content))
		return (0);
	wait(NULL);
	return (1);
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
	else if (tree->type == PIPE)
		return (exec_pipe(tree->left, tree->right));
	if (tree->left && tree->left->type != WORDS)
		exec_tree(tree->left);
	else if (tree->left && tree->left->type == WORDS)
		return (exec_function(tree->left->content));
	if (tree->right && tree->right->type != WORDS)
		exec_tree(tree->right);
	else if (tree->right && tree->right->type == WORDS)
		return (exec_function(tree->right->content));
	return (0);
}

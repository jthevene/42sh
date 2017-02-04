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

// int				exec_function(char *content)
// {
// 	if (content)
// 		return (1);
// 	else
// 		return (0);
// }

// int				exec_pipe(t_tree *left, t_tree *right)
// {
// /*
// 	if (left)
// 	{
// 		if (right)
// 			return (1);
// 		else
// 			return (0);
// 	}
// 	else
// 		return (0);
// */
// 	int			fd[2];
// 	pid_t		pid;

// 	pipe(fd);
// 	if ((pid = fork()) == -1)
// 		return (0);
// 	else if (pid == 0)
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		execve()
// 	}
// 	if (exec_function(left->content))
// 		;
// 	else
// 		return (0);
// }

// int				exec_tree(t_tree *tree)
// {
// 	if (!tree)
// 		return (0);
// 	if (tree->type == SEMICOLON)
// 	{
// 		exec_tree(tree->left);
// 		exec_tree(tree->right);
// 	}
// 	else if (tree->type == AND)
// 	{
// 		if (exec_tree(tree->left))
// 			exec_tree(tree->right);
// 	}
// 	else if (tree->type == OR)
// 	{
// 		if (!exec_tree(tree->left))
// 			exec_tree(tree->right);
// 	}
// 	else if (tree->type == PIPE)
// 		return (exec_pipe(tree->left, tree->right));

// 	if (tree->left && tree->left->type != WORDS)
// 		exec_tree(tree->left);
// 	else if (tree->left && tree->left->type == WORDS)
// 		return (exec_function(tree->left->content));
// 	if (tree->right && tree->right->type != WORDS)
// 		exec_tree(tree->right);
// 	else if (tree->right && tree->right->type == WORDS)
// 		return (exec_function(tree->right->content));
// 	return (0);
// }

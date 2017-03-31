/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:32 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

static int		exec_tree2(t_tree *tree)
{
	if (tree->type == PIPE)
		return (run_pipe(tree->left, tree->right));
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

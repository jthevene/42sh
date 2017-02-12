/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:25:31 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/12 15:25:33 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

t_tree		*create_node(void)
{
	t_tree *tree;

	if (!(tree = malloc(sizeof(t_tree))))
		return (NULL);
	tree->left = NULL;
	tree->right = NULL;
	tree->type = 0;
	tree->content = NULL;
	return (tree);
}

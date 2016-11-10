/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 16:44:56 by hjacque           #+#    #+#             */
/*   Updated: 2016/11/10 12:16:23 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_tree		*create_node(void)
{
	t_tree *tree;

	if (!(tree = malloc(sizeof(t_tree))))
		return (NULL);
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}
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

int			str_is_digit(char *str)
{
	unsigned int		i;

	i = 0;
	while (ft_isdigit((unsigned char)str[i]))
		i++;
	if (i == ft_strlen(str))
		return (1);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:23:44 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/12 15:23:46 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	free_tree(t_tree *tree)
{
	if (tree)
	{
		free(tree->content);
		if (tree->left)
			free_tree(tree->left);
		if (tree->right)
			free_tree(tree->right);
		free(tree);
	}
}

void	free_tab(char **tabl)
{
	int		i;

	i = 0;
	while (tabl && tabl[i])
	{
		free(tabl[i]);
		i++;
	}
	free(tabl);
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token->next)
	{
		tmp = token;
		free(tmp->lexeme);
		token = token->next;
		free(tmp);
	}
	free(token->lexeme);
	free(token);
}

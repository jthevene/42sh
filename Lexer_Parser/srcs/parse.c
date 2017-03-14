/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:41 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:45:51 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	parse(t_tree *tree, t_token *token)
{
	if (dotcoma(tree, token) == 0)
		if (and_or(tree, token) == 0)
			if (redirections(tree, token) == 0)
			{
				tree->type = WORDS;
				tree->content = commands_leaf(token);
			}
}

int		dotcoma(t_tree *tree, t_token *token)
{
	t_token *tmp;
	t_token *begin;

	begin = token;
	if (!(tmp = get_token(token, SEMICOLON)))
		return (0);
	tree->left = create_node();
	tree->right = create_node();
	tree->type = tmp->type;
	tree->content = ft_strdup(tmp->lexeme);
	FT_INIT(t_token*, left_token, copy_token_left(begin, tmp));
	FT_INIT(t_token*, right_token, copy_token_right(tmp));
	parse(tree->left, left_token);
	parse(tree->right, right_token);
	free_token(left_token);
	free_token(right_token);
	return (1);
}

int		and_or(t_tree *tree, t_token *token)
{
	t_token *tmp;
	t_token *begin;

	begin = token;
	if (!(tmp = get_token_and_or(token)))
		return (0);
	tree->left = create_node();
	tree->right = create_node();
	tree->type = tmp->type;
	tree->content = ft_strdup(tmp->lexeme);
	FT_INIT(t_token*, left_token, copy_token_left(begin, tmp));
	FT_INIT(t_token*, right_token, copy_token_right(tmp));
	parse(tree->left, left_token);
	parse(tree->right, right_token);
	free_token(left_token);
	free_token(right_token);
	return (1);
}

int		redirections(t_tree *tree, t_token *token)
{
	t_token *tmp;
	t_token *begin;

	begin = token;
	if (!(tmp = get_token_redirections(token)))
		return (0);
	tree->left = create_node();
	tree->right = create_node();
	tree->type = tmp->type;
	tree->content = ft_strdup(tmp->lexeme);
	FT_INIT(t_token*, left_token, copy_token_left(begin, tmp));
	FT_INIT(t_token*, right_token, copy_token_right(tmp));
	parse(tree->left, left_token);
	parse(tree->right, right_token);
	free_token(left_token);
	free_token(right_token);
	return (1);
}

char	*commands_leaf(t_token *token)
{
	t_token	*tmp;
	char	*leaf;

	FT_INIT(char*, tmp_leaf, NULL);
	tmp = token;
	leaf = NULL;
	while (tmp)
	{
		if (!(leaf))
			leaf = ft_strdup(tmp->lexeme);
		if (tmp->next)
		{
			tmp_leaf = leaf;
			leaf = ft_strjoinchar(leaf, tmp->next->lexeme, ' ');
			ft_strdel(&tmp_leaf);
		}
		tmp = tmp->next;
	}
	return (leaf);
}

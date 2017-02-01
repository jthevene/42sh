#include "../includes/sh.h"

void	start_parse(t_token *token)
{
	t_tree	*tree;

	tree = create_node();
	parse(tree, token);
	free_tree(tree);
}


t_token	*get_token(t_token *token, int type)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == type)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

t_token	*get_token_and_or(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == AND || tmp->type == OR)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

t_token	*get_token_redirections(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == PIPE || tmp->type == DLESS \
			|| tmp->type == DMORE || tmp->type == LESS \
			|| tmp->type == MORE)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

t_token	*copy_token_left(t_token *begin, t_token *ope)
{
	t_token	*left;
	t_token	*tmp;
	t_token	*begin_left;

	left = init_token();
	tmp = begin;
	begin_left = left;
	while (tmp->type != ope->type)
	{
		left->type = tmp->type;
		left->lexeme = ft_strdup(tmp->lexeme);
		if (tmp->next->type != ope->type)
			left->next = init_token();
		left = left->next;
		tmp = tmp->next;
	}
	return (begin_left);
}

t_token	*copy_token_right(t_token *ope)
{
	t_token	*right;
	t_token	*tmp;
	t_token	*begin_right;

	right = init_token();
	begin_right = right;
	tmp = ope->next;
	while (tmp)
	{
		right->type = tmp->type;
		right->lexeme = ft_strdup(tmp->lexeme);
		if (tmp->next)
			right->next = init_token();
		right = right->next;
		tmp = tmp->next;
	}
	return (begin_right);
}

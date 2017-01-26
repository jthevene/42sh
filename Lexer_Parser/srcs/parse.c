#include "../includes/sh.h"

void	parse(t_tree *tree, t_token *token)
{
	if (dotcoma(tree, token) == 0)
	{
		if (and_or(tree, token) == 0)
		{
			if (redirections(tree, token) == 0)
			{
				tree->type = token->type;
				tree->content = ft_strdup(token->lexeme);
				printf("{COMMAND}\n");
				printf("type : %d\n", tree->type);
				printf("content : (%s)\n\n", tree->content);
				//printf("left : (%s)\n", tree->left->content);
				//printf("right : (%s)\n", tree->right->content);
			}
			else
			{
				printf("{REDIRECTIONS}\n");
				printf("type : %d\n", tree->type);
				printf("content : (%s)\n", tree->content);
				printf("left : (%s)\n", tree->left->content);
				printf("right : (%s)\n\n", tree->right->content);
			}
		}
		else
		{
			printf("{AND_OR}\n");
			printf("type : %d\n", tree->type);
			printf("content : (%s)\n", tree->content);
			printf("left : (%s)\n", tree->left->content);
			printf("right : (%s)\n\n", tree->right->content);
		}
	}
	else
	{
		printf("{SEMICOLON}\n");
		printf("type : %d\n", tree->type);
		printf("content : (%s)\n", tree->content);
		printf("left : (%s)\n", tree->left->content);
		printf("right : (%s)\n\n", tree->right->content);
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
	parse(tree->left, copy_token_left(begin, tmp));
	parse(tree->right, copy_token_right(tmp));
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
	parse(tree->left, copy_token_left(begin, tmp));
	parse(tree->right, copy_token_right(tmp));
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
	parse(tree->left, copy_token_left(begin, tmp));
	parse(tree->right, copy_token_right(tmp));
	return (1);
}


#include "../includes/sh.h"

static int verif_content(char *content)
{
	return(ft_isope(content[0]));
}

void	parse(t_tree *tree, t_token *token)
{
	if (dotcoma(tree, token) == 0)
	{
		if (and_or(tree, token) == 0)
		{
			if (redirections(tree, token) == 0)
			{
				tree->type = token->type;
				tree->content = commands_leaf(token);
				//printf("{COMMAND}\n");
				//printf("type : %d\n", tree->type);
				//printf("content : (%s)\n\n", tree->content);
				
				//printf("left : (%s)\n", tree->left->content);
				//printf("right : (%s)\n", tree->right->content);
			}
			else
			{
				//printf("{REDIRECTIONS}\n");
				//printf("type : %d\n", tree->type);
				//printf("content : (%s)\n", tree->content);
				//printf("left : (%s)\n", tree->left->content);
				//printf("right : (%s)\n\n", tree->right->content);
			}
		}
		else
		{
			//printf("{AND_OR}\n");
			//printf("type : %d\n", tree->type);
			//printf("content : (%s)\n", tree->content);
			//printf("left : (%s)\n", tree->left->content);
			//printf("right : (%s)\n\n", tree->right->content);
			execute_or_and(tree);
		}
		ft_printf("direct content : (%s)\n\n", tree->content);
	}
	else
	{
//		printf("{SEMICOLON}\n");
//		printf("type : %d\n", tree->type);
//		printf("content : (%s)\n", tree->content);
//		printf("left : (%s)\n", tree->left->content);
//		printf("right : (%s)\n\n", tree->right->content);
//	printf("direct content : (%s)\n", tree->content);
		if (!verif_content(tree->left->content))
			distrib_functions(tree->left->content);
		if (!verif_content(tree->right->content))
			distrib_functions(tree->right->content);
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

	tmp = token;
	leaf = NULL;
	while (tmp)
	{
		if (!(leaf))
			leaf = ft_strdup(tmp->lexeme);
		if (tmp->next)
			leaf = ft_strjoinchar(leaf, tmp->next->lexeme, ' ');
		tmp = tmp->next;
	}
	return (leaf);
}

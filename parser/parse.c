#include "includes/parse.h"

void	parse(t_tree *tree)
{
	if (dotcoma(tree) == 0)
	{
		if (and_or(tree) == 0)
		{
			if (redirections(tree) == 0)
			{
				if (tree->content)
					tree->type = COMMAND;
				printf("{COMMAND}\n");
				printf("type : %d\n", tree->type);
				printf("content : (%s)\n", tree->content);
				//printf("left : (%s)\n", tree->left->content);
				//printf("right : (%s)\n", tree->right->content);
			}
			else
			{
				printf("{REDIRECTIONS}\n");
				printf("type : %d\n", tree->type);
				printf("content : (%s)\n", tree->content);
				printf("left : (%s)\n", tree->left->content);
				printf("right : (%s)\n", tree->right->content);
			}
		}
		else
		{
			printf("{AND_OR}\n");
			printf("type : %d\n", tree->type);
			printf("content : (%s)\n", tree->content);
			printf("left : (%s)\n", tree->left->content);
			printf("right : (%s)\n", tree->right->content);
		}
	}
	else
	{
		printf("{SEMICOLON}\n");
		printf("type : %d\n", tree->type);
		printf("content : (%s)\n", tree->content);
		printf("left : (%s)\n", tree->left->content);
		printf("right : (%s)\n", tree->right->content);
	}
}

int		dotcoma(t_tree *tree)
{
	char	*chr;
	int		len;


	if (!(chr = ft_strchr(tree->content, ';')))
		return (0);
	tree->left = create_node();
	tree->right = create_node();
	tree->type = SEMICOLON;
	tree->right->content = ft_strdup(chr + 1);
	tree->right->content = ft_epurstr(tree->right->content);
	len = chr - tree->content;
	tree->left->content = ft_strndup(tree->content, len);
	tree->left->content = ft_epurstr(tree->left->content);
	free(tree->content);
	tree->content = ft_strdup(";");
	parse(tree->left);
	parse(tree->right);
	return (1);
}

int		and_or(t_tree *tree)
{
	char	*chr;
	int		len;

	if (!(chr = search(tree->content, "&&", "||")))
		return (0);
	tree->left = create_node();
	tree->right = create_node();
	tree->right->content = ft_strdup(chr + 2);
	tree->right->content = ft_epurstr(tree->right->content);
	len = chr - tree->content;
	tree->left->content = ft_strndup(tree->content, len);
	tree->left->content = ft_epurstr(tree->left->content);
	free(tree->content);
	if (ft_strncmp(chr, "&&", 2) == 0)
	{
		tree->type = AND;
		tree->content = ft_strdup("&&");
	}
	else
	{
		tree->type = OR;
		tree->content = ft_strdup("||");
	}
	parse(tree->left);
	parse(tree->right);
	return (1);
}

int		redirections(t_tree *tree)
{
	char	*chr;
	int		len;

	len = 0;
	if (!(chr = search2(tree->content, "<", ">", "|")))
		return (0);
	tree->left = create_node();
	tree->right = create_node();
	if (ft_strncmp(chr, "<<", 2) == 0)
		dbless_tree(tree, chr, len);
	else if (ft_strncmp(chr, ">>", 2) == 0)
		dbmore_tree(tree, chr, len);
	else if (ft_strncmp(chr, "<", 1) == 0)
		less_tree(tree, chr, len);
	else if (ft_strncmp(chr, ">", 1) == 0)
		more_tree(tree, chr, len);
	else if (ft_strncmp(chr, "|", 1) == 0)
		pipe_tree(tree, chr, len);
	parse(tree->left);
	parse(tree->right);
	return (1);
}

void	pipe_tree(t_tree *tree, char *chr, int len)
{
	tree->type = PIPE;
	tree->left = create_node();
	tree->right = create_node();
	tree->right->content = ft_strdup(chr + 1);
	tree->right->content = ft_epurstr(tree->right->content);
	len = chr - tree->content;
	tree->left->content = ft_strndup(tree->content, len);
	tree->left->content = ft_epurstr(tree->left->content);
	free(tree->content);
	tree->content = ft_strdup("|");
}

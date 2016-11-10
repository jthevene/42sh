#include "includes/parse.h"

void	parse(t_tree *tree)
{
	if (dotcoma(tree) == 0)
	{
		printf("No ; !\n");
		printf("content : (%s)\n", tree->content);
		
	}
	else
	{
		printf("content : (%s)\n", tree->content);
		printf("left : (%s)\n", tree->left->content);
		printf("right : (%s)\n", tree->right->content);
	}
	//parse(tree->left);
	//parse(tree->right);
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
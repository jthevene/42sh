#include "includes/parse.h"

t_tree		*create_node(void)
{
	t_tree *tree;

	if (!(tree = malloc(sizeof(t_tree))))
		return (NULL);
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}
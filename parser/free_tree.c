#include "includes/parse.h"

void	free_tree(t_tree *tree)
{
	if (tree)
	{
		if (tree->left)
			free_tree(tree->left);
		if (tree->right)
			free_tree(tree->right);
		free(tree);
	}
}
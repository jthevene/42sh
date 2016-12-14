#include "../includes/parse.h"

void	exec_recursive(t_tree tree)
{
	exec_recursive(tree->left);
	exec_recursive(tree->right);
}
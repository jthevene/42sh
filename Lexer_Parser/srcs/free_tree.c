#include "../includes/sh.h"

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

#include "../includes/42sh.h"

int verif_content(char *content)
{
	return(ft_isope(content[0]));
}

int 		ft_pip(t_tree *tree)
{
	if (!tree || !tree->content || !tree->left || !tree->left->content 
		|| !tree->right || !tree->right->content)
		return (0);
	return (1);
}
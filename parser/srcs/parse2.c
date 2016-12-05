#include "../includes/parse.h"

void	dbless_tree(t_tree *tree, char *chr, int len)
{
	char	*tmp;

	tmp = chr + 3;
	tree->type = DBLESS;
	tree->left = create_node();
	tree->right = create_node();
	len = chr - tree->content;
	tree->left->content = ft_strndup(tree->content, len);
	tree->left->content = ft_epurstr(tree->left->content);
	while (*tmp != ' ' && *tmp != '\0')
		tmp++;
	tree->right->content = ft_strdup(tmp);
	tree->right->content = ft_epurstr(tree->right->content);
	len = tmp - chr;
	free(tree->content);
	tree->content = ft_strndup(chr, len);
	tree->content = ft_epurstr(tree->content);
}

void	dbmore_tree(t_tree *tree, char *chr, int len)
{
	char	*tmp;

	tmp = chr + 3;
	tree->type = DBMORE;
	tree->left = create_node();
	tree->right = create_node();
	len = chr - tree->content;
	tree->left->content = ft_strndup(tree->content, len);
	tree->left->content = ft_epurstr(tree->left->content);
	while (*tmp != ' ' && *tmp != '\0')
		tmp++;
	tree->right->content = ft_strdup(tmp);
	tree->right->content = ft_epurstr(tree->right->content);
	len = tmp - chr;
	free(tree->content);
	tree->content = ft_strndup(chr, len);
	tree->content = ft_epurstr(tree->content);
}

void	less_tree(t_tree *tree, char *chr, int len)
{
	char	*tmp;

	tmp = chr + 2;
	tree->type = LESS;
	tree->left = create_node();
	tree->right = create_node();
	len = chr - tree->content;
	tree->left->content = ft_strndup(tree->content, len);
	tree->left->content = ft_epurstr(tree->left->content);
	while (*tmp != ' ' && *tmp != '\0')
		tmp++;
	tree->right->content = ft_strdup(tmp);
	tree->right->content = ft_epurstr(tree->right->content);
	len = tmp - chr;
	free(tree->content);
	tree->content = ft_strndup(chr, len);
	tree->content = ft_epurstr(tree->content);
}

void	more_tree(t_tree *tree, char *chr, int len)
{
	char	*tmp;

	tmp = chr + 2;
	tree->type = MORE;
	tree->left = create_node();
	tree->right = create_node();
	len = chr - tree->content;
	tree->left->content = ft_strndup(tree->content, len);
	tree->left->content = ft_epurstr(tree->left->content);
	while (*tmp != ' ' && *tmp != '\0')
		tmp++;
	tree->right->content = ft_strdup(tmp);
	tree->right->content = ft_epurstr(tree->right->content);
	len = tmp - chr;
	free(tree->content);
	tree->content = ft_strndup(chr, len);
	tree->content = ft_epurstr(tree->content);
}

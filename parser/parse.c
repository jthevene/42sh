#include "includes/parse.h"

void	parse(t_tree *tree)
{
	if (dotcoma(tree) == 0)
		printf("No ; !\n");
	else
	{
		printf("content : (%s)\n", tree->content);
		printf("left : (%s)\n", tree->left->content);
		printf("right : (%s)\n", tree->right->content);
	}
	//parse(tree->left);
	//parse(tree->right);
}

t_tree		*create_node(void)
{
	t_tree *tree;

	if (!(tree = malloc(sizeof(t_tree))))
		return (NULL);
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

int		main(int ac, char **av)
{
	t_all	*all;
	t_tree	*tree;

	(void)ac;
	(void)av;
	tree = create_node();
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		return (0);
	while (93)
	{
		ft_putstr("$> ");
		get_next_line(0, &(all->line));
		if ((ft_strcmp(all->line, "\0") == 0) || (isallspace(all->line) == 1))
			;
		else
		{
			tree->content = epur_str(ft_strdup(all->line));
			all->epured = search(tree->content, "&&", "||");
			printf("search : %s\n", all->epured);
			parse(tree);
		}
	}
	return (0);
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
	tree->right->content = epur_str(tree->right->content);
	len = chr - tree->content;
	tree->left->content = ft_strndup(tree->content, len);
	tree->left->content = epur_str(tree->left->content);
	free(tree->content);
	tree->content = ft_strdup(";");
	return (1);
}
#include "includes/parse.h"

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
		if ((ft_strcmp(all->line, "\0") == 0) || (ft_isallspace(all->line) == 1))
			;
		else
		{
			tree->content = ft_epurstr(ft_strdup(all->line));
			parse(tree);
		}
	}
	free_tree(tree);
	return (0);
}
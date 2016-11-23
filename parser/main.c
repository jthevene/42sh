#include "includes/parse.h"

int		main(int ac, char **av, char **env)
{
	t_all	*all;
	t_tree	*tree;

	(void)ac;
	(void)av;
	tree = create_node();
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		return (0);
	all->envcpy = ft_tabdup(env);
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
			exec_tree(all, tree);
		}
	}
	free_tree(tree);
	return (0);
}

void	get_cmd(t_all *all, char *command)
{
	if (count_words(command) > 1)
		all->lines = ft_strsplit(command, ' ');
	else
	{
		all->lines = malloc(sizeof(char *) * 3);
		all->lines[0] = ft_strdup(command);
		all->lines[1] = NULL;
		all->lines[2] = NULL;
	}
	all->cmd = ft_strdup(all->lines[0]);
}

int		count_words(char *str)
{
	int		i;
	int		words;

	words = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			words++;
		i++;
	}
	return (words);
}

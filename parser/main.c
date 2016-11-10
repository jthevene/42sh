/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/21 16:44:56 by hjacque           #+#    #+#             */
/*   Updated: 2016/11/10 12:14:13 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
			tree->content = ft_epurstr(ft_strdup(all->line));
			all->epured = search(tree->content, "&&", "||");
			printf("search : %s\n", all->epured);
			parse(tree);
		}
	}
	return (0);
}
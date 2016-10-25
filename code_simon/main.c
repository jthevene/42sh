/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 17:16:37 by sgaudin           #+#    #+#             */
/*   Updated: 2016/10/13 10:58:25 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/redir.h"
#include "./includes/globing.h"

/*
static t_shell	*ft_init_gshell2(void)
{
	t_shell		*shell;

	if (!(shell = (t_shell *)malloc(sizeof(t_shell))))
	{
		printf("ft_init_shell Initialisation shell -> try again");
		exit(0);
	}
	shell->line = NULL;
	return (shell);
}
*/

void			ft_infinite_loop(void)
{
	int		ret;

	ret = 0;
	while (1)
	{
		ret = get_next_line(0, &g_shell.line); /* GNL leaking, careful !! */
		if (!ft_strcmp(g_shell.line, "exit"))
			exit(0);
		if (ret)
			glob_parser();
		free(g_shell.line);
		ft_putstr("\n$> ");
		ret = 0;
	}
}

int				main(int argc, char **argv, char **env)
{
	if (!argc || !argv || !env)
		return (0);
	g_shell.line = NULL;
//	g_shell = ft_init_gshell2();
	ft_putstr("$> ");
	ft_infinite_loop();
	return (0);
}

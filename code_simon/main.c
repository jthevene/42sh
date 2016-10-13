/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 17:16:37 by sgaudin           #+#    #+#             */
/*   Updated: 2016/10/07 13:21:52 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/redir.h"
#include "./includes/globing.h"

 static t_shell	*ft_init_gshell2(int argc, char *argv[], char *env[])
 {
 	t_shell		*shell;

 	if (!(shell = (t_shell *)malloc(sizeof(t_shell))))
 	{
 		ft_printf("ft_init_shell Initialisation shell -> try again");
 		exit(0);
 	}
 	shell->argc = argc;
 	shell->argv = argv;
 	shell->env = env;
 	shell->line = NULL;
 	shell->buf = NULL;
 	shell->tab_cmd = NULL;
 	return (shell);
 }

void			ft_infinite_loop(void)
{
	int		ret;

	ret = get_next_line(0, &g_shell->line);
	if (ret)
		glob_parser();
	free(g_shell->line);
	ft_putstr("\n$> ");
	while (1)
		;
}

int				main(int argc, char **argv, char **env)
{
	if (!argc || !argv || !env)
		return (0);
	g_shell = ft_init_gshell2(argc, argv, env);
	ft_putstr("$> ");
	ft_infinite_loop();
	free(g_shell);
	return (0);
}

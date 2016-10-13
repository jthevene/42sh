/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:40:03 by jules             #+#    #+#             */
/*   Updated: 2016/10/13 16:04:40 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

static int		init_env()
{
	int				i;
	char			*v_name;
	char			*v_value;
	t_var			*var;
	extern char		**environ;

	i = 0;
	if (!environ[0])
	{
		ft_putendl("error : no environ");
		return (0);
	}
	while (environ[i])
	{
		v_value = ft_strchr(environ[i], '=') + 1;
		v_name = ft_strsub(environ[i], 0, v_value - environ[i] - 1);
		var = new_var(v_name, v_value);
		ft_putstr("init_env1\n");
		ft_varappend(&g_shell->vars, var);
		ft_putstr("init_env2\n");
		free(v_name);
		i++;
	}
	g_shell->oldpwd = get_var(g_shell, "OLDPWD");
	g_shell->hist = (t_lst*)ft_memalloc(sizeof(t_lst));
	return (1);
}

int		init_all()
{
	ft_putstr("init_all1\n");
	ft_bzero(&g_shell, sizeof(t_shell));
	ft_signal();
	ft_putstr("init_all2\n");
	if (!init_env())
		return (1);
	g_shell->current_line = NULL;
	ft_putstr("init_all3\n");
	init_hist();
	tcgetattr(STDIN_FILENO, &g_shell->t_back);// save les données termios d'origine
	init_termios(g_shell->t_back);
	return (0);
}
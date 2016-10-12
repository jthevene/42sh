/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:40:03 by jules             #+#    #+#             */
/*   Updated: 2016/10/12 09:39:27 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

extern t_shell	g_shell;

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
		ft_varappend(&g_shell.vars, var);
		free(v_name);
		i++;
	}
	g_shell.oldpwd = get_var(&g_shell, "OLDPWD");
	g_shell.hist = (t_lst*)ft_memalloc(sizeof(t_lst));
	return (1);
}

int		init_all()
{
	ft_bzero(&g_shell, sizeof(t_env));
	init_signal();
	if (!init_env())
		return (1);
	g_shell.current_line = NULL;
	g_shell.buf = (*char)ft_memalloc(7); //pas sûr pour le 7
	init_hist();
	tcgetattr(STDIN_FILENO, &data->t_back);// save les données termios d'origine
	init_termios(g_shell->t_back);
	return (0);
}
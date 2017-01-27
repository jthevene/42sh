/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:40:03 by jules             #+#    #+#             */
/*   Updated: 2017/01/27 11:24:06 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

int		init_env()
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
		ft_varappend(var);
		free(v_name);
		i++;
	}
	g_shell.oldpwd = get_var(&g_shell, "OLDPWD");
	g_shell.hist = (t_lst*)ft_memalloc(sizeof(t_lst));
	return (1);
}	

void	init_hist_opt()
{
	g_shell.hist_opt->c = false;
	g_shell.hist_opt->d = false;
	g_shell.hist_opt->a = false;
	g_shell.hist_opt->r = false;
	g_shell.hist_opt->w = false;
	g_shell.hist_opt->p = false;
	g_shell.hist_opt->s = false;
}

void	init_hist()
{
	char	*filename;

	g_shell.hist_fd = 0;
	g_shell.hist = NULL;
	g_shell.nav_hist = 0;
	g_shell.curr_hist = NULL;
	init_hist_opt();
	filename = ft_strjoin(get_var(&g_shell, "HOME"), "/.history");
	g_shell.hist_fd = open(filename, O_RDWR | O_CREAT, 0600);
	ft_varappend(new_var("HISTSIZE", "4"));
	ft_varappend(new_var("HISTFILESIZE", "10"));
	get_hist();
	close(g_shell.hist_fd);
}

void	init_win()
{
	g_shell.win = ft_memalloc(sizeof(struct winsize));
	g_shell.win->ws_row = 0;
	g_shell.win->ws_col = 0;
	g_shell.win->ws_xpixel = 0;
	g_shell.win->ws_ypixel = 0;
	ioctl(0, TIOCGWINSZ, g_shell.win);
}

int		init_all()
{
 	t_shell		*shell;

 	if (!(shell = (t_shell *)malloc(sizeof(t_shell))))
 	{
 		ft_putendl("ft_init_shell Initialisation shell -> try again");
 		exit(0);
 	}
	ft_signal();
	if (!init_env())
		return (1);
	init_hist();
	init_win();
	g_shell.current_line = NULL;
	tcgetattr(STDIN_FILENO, &g_shell.t_back);// save les données termios d'origine
	init_termios(g_shell.t_back);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:40:03 by jules             #+#    #+#             */
/*   Updated: 2016/11/04 14:42:54 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

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
		ft_varappend(var);
		free(v_name);
		i++;
	}
	g_shell.oldpwd = get_var(&g_shell, "OLDPWD");
	g_shell.hist = (t_lst*)ft_memalloc(sizeof(t_lst));
	return (1);
}

void	init_hist()
{
	char	*filename;
 
	g_shell.hist_fd = 0;
	if (!(g_shell.hist = (t_lst*)malloc(sizeof(t_list))))
	{
		ft_putstr("g_shell.hist malloc failed");
		ft_reset_termios(g_shell.t_back);
		exit(0);
	}
	g_shell.hist->content = NULL;
	g_shell.hist->number = 0;
	g_shell.nav_hist = 0;
	g_shell.hist->next = NULL;
	g_shell.hist->prev = NULL;
	g_shell.last_hist = g_shell.hist;
	filename = ft_strjoin(get_var(&g_shell, "HOME"), "/.history");
	g_shell.hist_fd = open(filename, O_RDWR | O_CREAT, 0600);
	get_hist();
	close(g_shell.hist_fd);
}

static void		init_win()
{
	g_shell.win = ft_memalloc(sizeof(struct winsize));
	g_shell.win->ws_row = 0;
	g_shell.win->ws_col = 0;
	g_shell.win->ws_xpixel = 0;
	g_shell.win->ws_ypixel = 0;
	ioctl(0, TIOCGWINSZ, g_shell.win);

	g_shell.prev_win = ft_memalloc(sizeof(struct winsize));
	g_shell.prev_win->ws_row = g_shell.win->ws_row;
	g_shell.prev_win->ws_col = g_shell.win->ws_col;
	g_shell.prev_win->ws_xpixel = g_shell.win->ws_xpixel;
	g_shell.prev_win->ws_ypixel = g_shell.win->ws_ypixel;
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
//	init_hist();
	init_win();
	g_shell.current_line = NULL;
	g_shell.cursor_x = 3;
	g_shell.cursor_2d_x = 0;
	g_shell.cursor_2d_y = 0;
	g_shell.prev_cursor_x = 3;
	g_shell.prev_cursor_2d_x = 0;
	g_shell.prev_cursor_2d_y = 0;
	g_shell.line_2d_x = 3;
	g_shell.line_2d_y = 0;
	g_shell.nb_rows = 0;
	g_shell.line_size = 0;
	g_shell.prev_line_size = 0;
	g_shell.prev_line_2d_y = 0;
	g_shell.prev_line_2d_x = 0;
	g_shell.start_select = 0;
	g_shell.end_select = 0;
	g_shell.clipboard = NULL;
	g_shell.len = 0;
	g_shell.c = ft_strnew(16);
	tcgetattr(STDIN_FILENO, &g_shell.t_back);// save les données termios d'origine
	init_termios(g_shell.t_back);
	return (0);
}
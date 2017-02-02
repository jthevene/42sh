/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:40:03 by jules             #+#    #+#             */
/*   Updated: 2017/02/02 21:29:50 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

void	init_hist_opt()
{
	g_shell.hist_opt.c = false;
	g_shell.hist_opt.d = false;
	g_shell.hist_opt.a = false;
	g_shell.hist_opt.r = false;
	g_shell.hist_opt.w = false;
	g_shell.hist_opt.p = false;
	g_shell.hist_opt.s = false;
	g_shell.hist_opt.options = NULL;
	g_shell.hist_opt.arg = NULL;
	g_shell.hist_opt.filename = NULL;
}

void	init_hist()
{
	char	*filename;

	g_shell.hist_fd = 0;
	g_shell.hist = NULL;
	g_shell.nav_hist = 0;
	init_hist_opt();
	filename = ft_strjoin(get_var(&g_shell, "HOME"), "/.history");
	g_shell.hist_fd = open(filename, O_RDWR | O_CREAT, 0600);
	ft_varappend(new_var("HISTSIZE", "500"));
	ft_varappend(new_var("HISTFILESIZE", "500"));
	get_hist();
	g_shell.curr_hist = g_shell.hist;
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
}

static void 	init_edition()
{
	g_shell.current_line = NULL;
	g_shell.line = NULL;
	g_shell.cursor_x = 3;
	g_shell.cursor_2d_x = 0;
	g_shell.cursor_2d_y = 0;
	g_shell.line_2d_x = 3;
	g_shell.line_2d_y = 0;
	g_shell.nb_rows = 0;
	g_shell.line_size = 0;
	g_shell.prev_line_2d_y = 0;
	g_shell.start_select = 0;
	g_shell.end_select = 0;
	g_shell.clipboard = NULL;
	g_shell.len = 0;
	g_shell.c = ft_strnew(16);
	g_shell.prompt = 0;
	g_shell.prompt_len = 0;

	g_shell.result_exec = -99;
	g_shell.all_results = -99;
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
	init_edition();
	tcgetattr(STDIN_FILENO, &g_shell.t_back);// save les données termios d'origine
	init_termios(g_shell.t_back);
	return (0);
}
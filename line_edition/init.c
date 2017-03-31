/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:42 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/24 13:16:00 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

void			init_hist_opt(void)
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

void			init_hist(void)
{
	FT_INIT(char *, filename, NULL);
	FT_INIT(char*, home, get_var(g_shell.env, "HOME"));
	g_shell.hist_fd = 0;
	g_shell.hist = NULL;
	g_shell.nav_hist = 0;
	g_shell.saved_current_line = NULL;
	init_hist_opt();
	filename = ft_strjoin(home, "/.history");
	g_shell.hist_fd = open(filename, O_RDWR | O_CREAT, 0600);
	ft_varappend(new_var("HISTSIZE", "500"), &g_shell.env);
	ft_varappend(new_var("HISTFILESIZE", "500"), &g_shell.env);
	get_hist();
	g_shell.curr_hist = g_shell.hist;
	free(filename);
	free(home);
	close(g_shell.hist_fd);
}

static void		init_win(void)
{
	g_shell.win = ft_memalloc(sizeof(struct winsize));
	g_shell.win->ws_row = 0;
	g_shell.win->ws_col = 0;
	g_shell.win->ws_xpixel = 0;
	g_shell.win->ws_ypixel = 0;
	ioctl(0, TIOCGWINSZ, g_shell.win);
}

static void		init_edition(void)
{
	g_shell.current_line = NULL;
	g_shell.line = getcwd(NULL, 1024);
	g_shell.cursor_x = 3;
	g_shell.cursor_2d_x = 0;
	g_shell.cursor_2d_y = 0;
	g_shell.line_2d_x = 3;
	g_shell.line_2d_y = 0;
	g_shell.nb_rows = 0;
	g_shell.line_size = 0;
	g_shell.prev_line_2d_y = 0;
	g_shell.prev_cursor_2d_y = 0;
	g_shell.start_select = 0;
	g_shell.end_select = 0;
	g_shell.clipboard = NULL;
	g_shell.len = 0;
	g_shell.c = ft_strnew(16);
	g_shell.prompt = 0;
	g_shell.prompt_len = 0;
	g_shell.result_exec = -99;
	g_shell.all_results = -99;
	g_shell.sig = -1;
}

int				init_all(char **envp)
{
	ft_signal();
	if (!init_env(envp))
		return (1);
	init_hist();
	init_win();
	init_edition();
	g_shell.tmp_env = NULL;
	g_shell.left_redir_fd = -1;
	g_shell.right_redirs = NULL;
	g_shell.aggreg = NULL;
	g_shell.save_list = (t_save_fd *)malloc(sizeof(t_save_fd));
	g_shell.save_list->save_stdin = -1;
	g_shell.save_list->save_stdout = -1;
	g_shell.save_list->save_stderr = -1;
	g_shell.null_env = 0;
	tcgetattr(STDIN_FILENO, &g_shell.t_back);
	init_termios(g_shell.t_back);
	return (0);
}

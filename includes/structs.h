/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <dvirgile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/31 15:13:09 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# ifndef SH42_H
#  include "sh42.h"
# endif

typedef struct				s_file
{
	char					*name;
	int						type;
	int						len;
	char					*absolute_path;
	int						nb_elem;
	struct s_file			*next;
}							t_file;

typedef struct				s_completion
{
	struct s_file			*elem;
	struct s_completion		*next;
}							t_completion;

typedef struct				s_lst
{
	void					*content;
	struct s_lst			*prev;
	struct s_lst			*next;
	int						number;
}							t_lst;

typedef struct				s_var
{
	char					*name;
	char					*value;
	struct s_var			*next;
}							t_var;

typedef struct				s_hist_opt
{
	bool					c;
	bool					d;
	bool					a;
	bool					r;
	bool					w;
	bool					p;
	bool					s;
	char					*filename;
	char					*arg;
	char					*options;
}							t_hist_opt;

typedef struct				s_fdlist
{
	int						type;
	int						fd_in;
	int						fd_file;
	char					*filename;
	struct s_fdlist			*prev;
	struct s_fdlist			*next;
}							t_fdlist;

typedef struct				s_save_fd
{
	int						save_stdin;
	int						save_stdout;
	int						save_stderr;
}							t_save_fd;

typedef struct				s_quotes
{
	int						sq;
	int						dq;
	int						bq;
	int						aco;
	int						cro;
	int						par;
}							t_quotes;

typedef struct				s_shell
{
	int						len;
	char					*c;
	char					*oldpwd;
	char					*clipboard;
	char					*prompt;
	char					*current_line;
	int						env_opt;
	t_var					*env;
	t_var					*tmp_env;
	int						prompt_len;
	int						start_select;
	int						result_exec;
	int						all_results;
	int						end_select;
	int						cursor_x;
	int						cursor_2d_x;
	int						cursor_2d_y;
	int						line_2d_x;
	int						line_2d_y;
	int						line_size;
	int						prev_line_2d_y;
	int						prev_cursor_2d_y;
	int						nb_rows;
	struct winsize			*win;
	int						running;
	t_lst					*hist;
	t_lst					*curr_hist;
	int						hist_fd;
	t_lst					*end_hist_file;
	t_hist_opt				hist_opt;
	char					*saved_current_line;
	int						nav_hist;
	struct termios			my_termios;
	struct termios			t_back;
	char					*line;
	t_fdlist				*aggreg;
	t_fdlist				*right_redirs;
	int						left_redir_fd;
	t_save_fd				*save_list;
	int						null_env;
	pid_t					sig;
}							t_shell;

t_shell						g_shell;

#endif

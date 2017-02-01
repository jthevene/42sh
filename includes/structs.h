/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 16:40:01 by dvirgile          #+#    #+#             */
/*   Updated: 2017/01/31 17:41:29 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef STRUCTS_H
#  define STRUCTS_H

# ifndef _42SH_H
#  include "42sh.h"
# endif

typedef struct				s_file
{
	char					*name;
	int 					type;
	int 					len;
	char 					*absolute_path;
	int 					nb_elem;
	struct s_file			*next;
}							t_file;

typedef struct				s_completion
{
	struct s_file 			*elem;
	struct s_completion		*next;
}							t_completion;

typedef struct 		s_lst
{
	void			*content;
	struct s_lst	*prev;
	struct s_lst	*next;
	int 			number;
} 					t_lst;

typedef struct		s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}					t_var;

typedef struct 		s_hist_opt
{
	bool			c;
	bool			d;
	bool			a;
	bool			r;
	bool			w;
	bool			p;
	bool			s;
	char			**argument;
	char			*options;
}					t_hist_opt;

typedef struct			s_shell
{
	int 				len;
	char 				*c;
	char				*oldpwd;
	char 				*clipboard;
	char 				*prompt;
	char				*current_line; //ligne en cours d'edition
	t_var				*env; //contenu de ENV
	int 				prompt_len;
	int 				start_select;

	int 				result_exec;
	int 				all_results;

	int 				end_select;
	int 				cursor_x;
	int 				cursor_2d_x;
	int 				cursor_2d_y;
	int 				line_2d_x;
	int 				line_2d_y;
	int 				line_size;
	int 				prev_line_2d_y;
	int 				nb_rows; // 0 = premiere ligne de la commande en cours d'edition
	struct winsize		*win;
	int					running;
	t_lst				*hist;
	////////////////////////////	JULES PART
	t_lst				*curr_hist;
	int 				hist_fd;
	t_lst				*last_hist; //derniere ligne de l'historique
	t_lst				*end_hist_file; //derniere ligne du fichier history
	t_hist_opt			hist_opt;
	int 				nav_hist; // 0 = pas encore navigué dans l'historique
	///////////////////////////		END JULES
	struct termios		my_termios;
	struct termios		t_back;
	char				*line; // VARIABLE SIMON
}						t_shell;

t_shell		g_shell;

# endif
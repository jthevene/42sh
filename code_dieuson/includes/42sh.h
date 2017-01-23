/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/07 18:51:39 by jthevene          #+#    #+#             */
/*   Updated: 2016/12/08 14:01:07 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _42SH_H
# define _42SH_H

# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <term.h>
# include <sys/ioctl.h>
# include <curses.h>

# ifndef SH_LIBFT
#  define SH_LIBFT
#  include "../../libft/includes/libft.h"
# endif

# define K_PRINT   		1 //caractere imprimable
# define K_ESCAPE  		2
# define K_UP      		3
# define K_DOWN    		4
# define K_RIGHT   		5
# define K_LEFT    		6
# define K_DEL	   		7
# define K_BACKSP  		8
# define K_RETURN  		9
# define K_UNKNOWN		10
# define K_OW_RIGHT  	11
# define K_OW_LEFT 	  	12
# define K_OL_UP 	  	13
# define K_OL_DOWN 	  	14
# define K_GO_START	  	15
# define K_GO_END	  	16
# define K_COPY	  		17
# define K_CUT	  		18
# define K_PAST	  		19
# define K_TAB     		20

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

typedef struct		s_shell
{
	char 			*c;
	int 			len;
	char			*oldpwd;
	char 			*clipboard;
	t_var			*vars;//contenu de ENV
	int 			start_select;
	int 			end_select;
	int 			cursor_x;
	int 			cursor_2d_x;
	int 			cursor_2d_y;
	int 			prev_cursor_x;
	int 			prev_cursor_2d_x;
	int 			prev_cursor_2d_y;
	int 			line_2d_x;
	int 			line_2d_y;
	int 			line_size;
	int 			prev_line_size;
	int 			prev_line_2d_y;
	int 			prev_line_2d_x;
	int 			nb_rows; // 0 = premiere ligne de la commande en cours d'edition
	struct winsize	*win;
	struct winsize	*prev_win;
	int				running;
	t_lst			*hist;
	////////////////////////////	JULES PART
	int 			hist_fd;
	t_lst			*last_hist; //derniere ligne de l'historique
	t_lst			*end_hist_file; //derniere ligne du fichier history
	int 			nav_hist; // 0 = pas encore navigué dans l'historique
	///////////////////////////		END JULES
	struct termios	my_termios;
	struct termios	t_back;
	char			*current_line; //ligne en cours d'edition
	char			buf[8]; //pas sur qu'on en ait besoin en fait
	char			*line; // VARIABLE SIMON
}					t_shell;

t_shell		g_shell;

/*
** AUTO_COMLETION
*/
void 						free_int_tab(float *tab_to_del, int len);
void 						free_lists(t_file *match_files);
void 						free_lst_lst(t_completion *lst_lst);
void						free_auto_tab(char **table);
void 						free_files(t_file **files_list);

int 						arrondi(float val);
int 						ft_nb_elem_lst(int nb_elem, int nb_col);
int 						prev_sentence_value(char *sentence);
int 						verif_sentence(char *sentence);

char						*set_sentence(char *str, int len_str, char *name);
char 						*set_copy_sentence(char *sentence);
char 						*set_end_path(char **new_path, char **sentence);

t_file						*sort_list(t_file *files);
char 						*default_sentence(char **sentence);
char						*detect_auto_completion(char *sentence);
t_file 						*store_files_dirs(DIR *rep, t_file *files, char *path, char *to_search);
t_file 						*compare_list_sentence(t_file *files, char *sentence);
char 						**set_path(char **sentence, char *home, char *current_path);
void 						display_completion(char *sentence, t_file *match_files);
t_completion 				*build_lst_lst(t_file *match_files, int nb_elem, int nb_col);
char 						*similarity(t_file *match_files, char *sentence);
/*
** CATCH_KEY
*/
void 		set_2d_line_val();
void 		set_2d_cursor_val();
int					readkey(void);
/*
** CURSOR_MOVE
*/
int					ft_cursor_right(int i);
int 				distrib_cursor_mooves(int key);
void 				arrow_moove_left();
void 				arrow_moove_right();
void 				go_to_end();
/*
** HISTORY
*/
void				get_hist(void);
void				init_hist();
void				ft_newhist(char *line);
void				navigation_hist(int arrow);
void				ft_history(int i);
/*
** HISTORY2
*/
void				clear_history_list(void);
void				delete_line_history(int i);
void				show_hist_list(void);
void				update_history_file(void);
 /*
 ** INIT
 */
int					init_all(void);
void				init_hist(void);
/*
** LINE_EDITION
*/
void				fill_current_line(char c);
void 				copy_cut_line(int key);
void 				past_line(char *clipboard);
/*
** MAIN
*/
void				display_prompt(void);
/*
** PRINT_LINE
*/
void				clean_line();
void				print_line(int i);
/*
** RETURN_KEY
*/
void				return_key(void);
void				backspace_key(int key);
/*
** SIGNAL
*/
void				ft_signal(void);
void 				ft_sigkill(int sig);
/*
** TERMIOS
*/
int					init_termios(struct termios my_termios);
void				ft_reset_termios(struct termios t_back);
/*
** VAR
*/
char				*get_var(t_shell *g_shell, char *n_var);
t_var				*new_var(char *v_name, char *v_value);
void				ft_varappend(t_var *new_element);

// SIMON
int					glob_parser(void);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/07 18:51:39 by jthevene          #+#    #+#             */
/*   Updated: 2017/01/29 13:23:27 by jules            ###   ########.fr       */
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
# include <errno.h>

# ifndef LIBFT_H
#  include "../libft/includes/libft.h"
# endif

# ifndef STRUCTS_H
#  include "structs.h"
# endif

# ifndef GLOBING_H
#  include "globing.h"
# endif

# ifndef HISTORIQUE_H
#  include "history.h"
# endif

# ifndef SH_H
#  include "../../Lexer_Parser/includes/sh.h"
# endif

# define K_PRINT   		1
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
** CD
*/
void 				cd(char *line);
void				remove_last_dir(char **str, char c);
char		 		*path_converter(char *sentence, char *home, char *pwd);
/*
** CATCH_KEY
*/
void 				set_2d_line_val();
void 				set_2d_cursor_val();
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
** INIT
*/
void				init_hist_opt();
int					init_all(void);
void				init_hist(void);
int					init_env(void);
/*
** LINE_EDITION
*/
void				fill_current_line(char c);
void 				copy_cut_line(int key);
void 				past_line(char *clipboard);
char			 	*set_prompt(char *pwd);
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
** SIMON
*/
int					glob_parser(void);

/*
** BUILTINS
*/
int					_42sh_echo(char *line);
int					_42sh_env(void);
int					_42sh_setenv(char *line);
int					_42sh_unsetenv(char *name);

char				*get_var(t_shell *g_shell, char *n_var);
void				ft_varappend(t_var *new_element);
t_var				*new_var(char *v_name, char *v_value);
void				detect_builtins(void);

#endif

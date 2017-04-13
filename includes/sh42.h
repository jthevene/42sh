/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh42.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/13 17:04:00 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/13 10:42:28 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH42_H
# define SH42_H

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
# define SIMPLE 1
# define DOUBLE 2
# define IS_NOT_BUILTIN 0
# define IS_BUILTIN 1
# define DEFAULT 0
# define TMP 1
# define OTHER 2

/*
** AUTO_COMLETION
*/
void				free_int_tab(float *tab_to_del, int len);
void				free_lists(t_file *match_files);
void				free_lst_lst(t_completion *lst_lst);
void				free_auto_tab(char **table);
void				free_files(t_file **files_list);

int					arrondi(float val);
int					verif_bins(char *sentence);
int					ft_nb_elem_lst(int nb_elem, int nb_col);
int					prev_sentence_value(char *sentence);
int					verif_sentence(char *sentence);
char				*set_sentence(char *str, int len_str, char *name);
char				*set_copy_sentence(char *sentence);
char				*set_end_path(char **new_path, char **sentence);
t_file				*sort_list(t_file *files);
char				*default_sentence(char **sentence);
char				*detect_auto_completion(char *sentence, bool detect_bins);
t_file				*store_files_dirs(DIR *rp, t_file *f, char *pth, char *sh);
t_file				*compare_list_sentence(t_file *files, char *sentence);
char				**set_path(char **sentence, char *home, char *current_path,
					bool detect_bins);
void				display_completion(char *sentence, t_file *match_files);
t_completion		*build_lst_lst(t_file *matchfiles, int nbelem, int nbcol);
char				*similarity(t_file *match_files, char *sentence);
char				**clear_path(char **sentence);
t_completion		*change_col(t_completion *all_col, t_completion *head,
						int *ref_col, int nb_elem);
int					ask_to_show_data(float *disp_val);
float				*get_display_values(t_file *match_files);
char				*str_to_search(char *sentence);

/*
** CD
*/
int					cd(char *line);
void				remove_last_dir(char **str, char c);
char				*path_converter(char *sentence, char *home, char *pwd);
int					error_cd(char *type, char *file);
char				**lsh_read_line(char *line);
int					verif_access(char **path, char **file, char *option);
void				free_cd_vars(char **home, char **sentence, char **file
								, char **pwd);
char				*ft_rescue_directory(void);
void				cd_suite(char **file, char **path, char *option
							, int *len_tab);

/*
** CATCH_KEY
*/
void				set_2d_edition_val(void);
int					detect_arrow(char *key);
int					readkey(void);
/*
** CURSOR_MOVE
*/
int					ft_cursor_right(int i);
int					distrib_cursor_moves(int key);
void				arrow_move_left();
void				arrow_move_right();
void				move_cursor_n_to_direction(int n, int direction);
void				go_to_end();
/*
** INIT
*/
void				init_hist_opt();
int					init_all(char **envp);
void				init_hist(void);
int					init_env(char **envp);
void				init_tmp_env(void);
/*
** LINE_EDITION
*/
void				fill_current_line(char c);
void				copy_cut_line(int key);
void				past_line(char *clipboard);
char				*set_prompt(char *pwd);
/*
** MAIN
*/
void				display_prompt(void);
/*
** PRINT_LINE
*/
void				clean_line();
void				print_line(int i);
void				reset_cursor_pos(void);
int					set_cursor_start(int len, int ref_cursor);
/*
** RETURN_KEY
*/
void				return_key(void);
void				backspace_key(int key);
void				reset_line(void);
/*
** SIGNAL
*/
void				ft_signal(void);
void				ft_sigkill(int sig);
void				ft_sigint(int sig);
/*
** TERMIOS
*/
int					init_termios(struct termios my_termios);
void				ft_reset_termios(struct termios t_back);
/*
** BUILTINS
*/
int					ft_echo(char *line);
int					ft_env(char *cmd);
int					ft_setenv(char *line, int env);
int					ft_unsetenv(char *name);
char				*get_var(t_var *env, char *n_var);
void				ft_exit(char *return_value);
void				ft_varappend(t_var *new_element, t_var **env);
t_var				*new_var(char *v_name, char *v_value);
void				print_env(char *to_exec, int is_opt);
void				create_tmp_env(char **args, int is_opt);
void				save_old_tmp_env(t_var **old_tmp_env);
void				restore_new_env(t_var **old_tmp_env);
void				free_env(int env, t_var **old_tmp_env);
/*
** EXECUTION
*/
int					detect_builtins(char *to_exec, char *command_line);
void				handle_redirections(int is_builtin);
char				**get_bin_directories(void);
int					verif_access_others(char *path);
int					verif_access_bin(char *path);
char				**get_args(char *content);
char				**lst_to_tab(t_var *env);
int					lenght_list(t_var *env);
int					exec_function(char **content);
int					error_exec(char **args, char **cmd);
int					error_parse_bin(char *error);
/*
** REDIRECTIONS
*/
int					call_redirections(char **content);
char				*hub_right_redir(char *line);
char				*hub_simple_left_redir(char *line);
int					hub_aggreg(char **cmd);
int					get_fd_in(char *line, int i);
char				*delete_right_redirs_str(char *str);
void				nav_to_delete_redir(char *str, int *i, int *j);
char				*get_filename(char *line, int i);
int					push_right_redir(char *f, int in, int type, t_fdlist **lst);
t_fdlist			*new_node_fdlist(char *filename, int fd_in, int type);
void				stock_redirs_in_gshell(t_fdlist *fdlist);
int					fd_already_in_fdlist(t_fdlist **fdlist, int fd);
void				free_fdlist(t_fdlist **fdlist, int close);
void				go_save_fd(t_save_fd **save_list, int fd_to_save);
void				restablish_fd(t_save_fd **save_list);
int					start_aggreg(char **cmd, int *fd_in, int *fd_out,
								t_fdlist **tmp);
int					detect_aggreg(char **cmd, int *fd_in, int *fd_out);
int					pushback_aggreg(t_fdlist **flist, int fd_in, int fd_out);
void				free_aggreg(void);
int					get_fd_to_close(int fd);
int					free_tmp_aggreg(t_fdlist **tmp);
void				free_right_redir(void);

void				ft_sigkill(int sig);
void				ft_sigint(int sig);
void				interrupt_prompt(int sig);
int					len_tab(char **tabl);
char				**verif_dirs(char **tabl);
int					verif_access_bin_directory_(char *path);
void				parse_capabilities(int key);

#endif

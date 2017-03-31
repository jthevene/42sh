/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <dvirgile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/31 15:13:47 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# ifndef SH42_H
#  include "sh42.h"
# endif

/*
** ERROR
*/
void				ft_error(char *str);
void				ft_out_of_range(int i);
/*
** EVENT
*/
int					ft_strisnum(char *nbr);
char				*event_n(int n, char *type);
char				*event_str(char *str, char *type);
int					history_event(char *event);
/*
** FT_HISTORY
*/
int					check_hist_opt();
int					history_hub(char *line);
void				ft_history_print(t_lst *lst);
void				ft_history(char *nbr);
void				show_hist_list();
/*
** FT_HISTORY_OPTIONS
*/
void				get_history_options();
void				clear_history_list(void);
void				delete_line_history(char *nbr);
void				show_hist_list(void);
void				update_history_file(int histfilesize);
void				histfile_append();
/*
** GET_PATH
*/
t_lst				*get_dir_content(char *dir);
/*
** HISTORIC
*/
void				free_hist(void);
void				get_hist(void);
void				ft_newhist(char *line);
void				put_hist_line(char *content);
/*
** HISTORY_LEXING
*/
int					invalid_option(void);
void				free_hist_opt(void);
void				split_line(char *line);
void				get_arg_filename(int i, char **array);
int					get_options_str(char **array);
/*
** HISTSIZE
*/
void				update_histfilesize(int histfilesize);
void				update_histsize(int histsize);
int					get_histsize(char *var);
/*
** LST_TOOLS
*/
t_lst				*ft_newlst(char *content);
void				ft_append_lst(t_lst **lst, t_lst *new_elem);
void				ft_print_list_content(t_lst *lst);
void				ft_lst_rewind_n(t_lst **lst, int n);
void				ft_lst_rewind(t_lst **lst);
void				ft_lst_forward(t_lst **lst);
/*
** NAVIGATION_HIST
*/
void				navigation_hist(int arrow);
void				nav_hist_up(void);
void				nav_hist_down(void);
#endif

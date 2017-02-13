/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/07 18:51:39 by jthevene          #+#    #+#             */
/*   Updated: 2017/02/13 12:38:13 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# ifndef _21SH_H
#  include "21sh.h"
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
void				show_hist_list();
void				get_hist(void);
void				ft_newhist(char *line);
void				put_hist_line(char *content);
void				navigation_hist(int arrow);
/*
** HISTORY_LEXING
*/
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

#endif

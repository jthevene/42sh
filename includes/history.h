/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/07 18:51:39 by jthevene          #+#    #+#             */
/*   Updated: 2017/01/29 13:37:35 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# ifndef I_42SH_H
#  define I_42SH_H
#  include "./42sh.h"
# endif

/*
** ERROR
*/
void				ft_error(char *str);
void				ft_out_of_range(int i);
/*
** EVENT
*/
char				*event_n(int n);
void				check_pattern_event(char *event);
/*
** FT_HISTORY
*/
void				ft_history_print(t_lst *lst);
void				ft_history(char *nbr);
/*
** FT_HISTORY_OPTIONS
*/
void				clear_history_list(void);
void				delete_line_history(int i);
void				show_hist_list(void);
void				update_history_file(char *filename, int histfilesize);
void				option_p(void);
/*
** GET_PATH
*/
t_lst				*get_dir_content(char *dir);
/*
** HISTORIC
*/
void				get_hist(void);
void				ft_newhist(char *line);
void				put_hist_line(char *content);
void				navigation_hist(int arrow);
/*
** HISTSIZE
*/
void				update_histfilesize(int histfilesize);
void				update_histsize(int histsize);
int 				get_histsize(char *var);
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

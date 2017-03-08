/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:45:58 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# ifndef SH21_H
#  include "sh21.h"
# endif

# ifndef FT_INIT
#  define FT_INIT(type, name, value) type name = value
# endif

int					simple_right();
int					double_right();
int					detect_out();
void				exec_redir_right(int fd);
int					create_file(char *filename, t_fdlist **fdlist, int type);

#endif

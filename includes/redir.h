/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 18:56:17 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/13 12:38:09 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# ifndef _21SH_H
#  include "21sh.h"
# endif

# ifndef FT_INIT
#  define FT_INIT(type, name, value) type name = value
# endif

int					simple_right();
int					double_right();
int					detect_out();
void				exec_redir_right(int fd/*, int fd_out*/);
int					create_file(char *filename, t_fdlist **fdlist, int type);

#endif

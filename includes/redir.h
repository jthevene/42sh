/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 18:56:17 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/10 11:45:24 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# ifndef _42SH_H
#  include "42sh.h"
# endif

# ifndef FT_INIT
#  define FT_INIT(type, name, value) type name = value
# endif

# define SIMPLE 1
# define DOUBLE 2

typedef struct		s_fdlist
{
	int				key;
	struct s_fdlist	*prev;
	struct s_fdlist	*next;
}					t_fdlist;

int					simple_right();
int					double_right();
int 				simple_left();
int					detect_out();
void				exec_redir_right(int fd/*, int fd_out*/);
int					create_file(char *filename, t_fdlist **fdlist, int type);
void				free_fdlist(t_fdlist **fdlist);

#endif

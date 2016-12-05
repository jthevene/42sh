/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 18:56:17 by sgaudin           #+#    #+#             */
/*   Updated: 2016/11/15 18:56:18 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# ifndef I_42SH_H
#  define I_42SH_H
#  include "../../code_dieuson/includes/42sh.h"
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

int					detect_out();
void				exec_redir_right(int fd/*, int fd_out*/);
int					create_file(char *filename, t_fdlist **fdlist, int type);
void				free_fdlist(t_fdlist **fdlist);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/07 18:51:39 by jthevene          #+#    #+#             */
/*   Updated: 2016/10/12 09:35:20 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef 42SH_H
# define 42SH_H

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
# include <curses.h>
# include "../libft/libft.h"

typedef struct 		s_lst
{
	void			*content;
	struct s_lst	*prev;
	struct s_lst	*next;
} 					t_lst;

typedef struct		s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}					t_var;

typedef struct		s_shell
{
	char			*oldpwd;
	t_var			*vars;
	int				running;
	t_lst			*hist;
	struct termios	my_termios;
	struct termios	t_back;
	char			*current_line;
	char			buf[7];
}					t_shell;

/*
** HISTORY
*/
void				init_hist();
void				ft_newhist(char *line);
/*
** INIT
*/
int					init_all();
/*
** TERMIOS
*/
int		ft_init_termios(struct termios my_termios);
void	ft_reset_termios(struct termios t_back);
/*
** VAR
*/
t_var				*new_var(char *v_name, char *v_value);
void				ft_varappend(t_var **alst, t_var *new_element);

#endif

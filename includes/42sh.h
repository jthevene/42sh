/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42sh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/07 18:51:39 by jthevene          #+#    #+#             */
/*   Updated: 2016/11/08 11:48:08 by jules            ###   ########.fr       */
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
# include "../libft/includes/libft.h"

# define K_PRINT   1 //caractere imprimable
# define K_ESCAPE  2
# define K_UP      3
# define K_DOWN    4
# define K_RIGHT   5
# define K_LEFT    6
# define K_DEL	   7
# define K_BACKSP  8
# define K_RETURN  9
# define K_UNKNOWN 10

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
	t_var			*vars;//contenu de ENV
	int 			cursor_x;
	int 			cursor_y; // 0 = premiere ligne de la commande en cours d'edition
	struct winsize	*win;
	int				running;
	t_lst			*hist;
	struct termios	my_termios;
	struct termios	t_back;
	char			*current_line; //ligne en cours d'edition
	char			buf[8]; //pas sur qu'on en ait besoin en fait
	char			*line; // VARIABLE SIMON
}					t_shell;

t_shell		g_shell;

/*
** CATCH_KEY
*/
int					readkey(void);
/*
** CURSOR_MOVE
*/
void				ft_cursor_right(int i);
void				ft_cursor_left(int i);
void				cursor_next_line(void);
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
** LINE_EDITION
*/
void				fill_current_line(char c);
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
void				backspace_key(void);
/*
** SIGNAL
*/
void				ft_signal(void);
/*
** TERMIOS
*/
int					init_termios(struct termios my_termios);
void				ft_reset_termios(struct termios t_back);
/*
** VAR
*/
char				*get_var(t_shell *g_shell, char *n_var);
t_var				*new_var(char *v_name, char *v_value);
void				ft_varappend(t_var *new_element);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_completion_tools.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 12:09:07 by sgaudin           #+#    #+#             */
/*   Updated: 2017/03/28 12:09:08 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

float			*get_display_values(t_file *match_files)
{
	FT_INIT(float*, tab_val, (float*)malloc(sizeof(float) * 6));
	tab_val[0] = (float)match_files->nb_elem;
	tab_val[1] = (float)match_files->len;
	tab_val[2] = arrondi(g_shell.win->ws_col / (tab_val[1] + 2));
	tab_val[3] = g_shell.win->ws_row;
	tab_val[4] = ft_nb_elem_lst(tab_val[0], tab_val[2]);
	tab_val[5] = g_shell.win->ws_row - (g_shell.line_2d_y + 1);
	return (tab_val);
}

void			ft_sigint_completion(int sig)
{
	(void)sig;
	tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
	tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
	tputs(tgetstr("cd", NULL), 1, ft_putchar_int);
	ft_putstr("Choose (y or n)\n");
}

static void		print_choice(float *disp_val)
{
	ft_putstr("Display all ");
	ft_putnbr((int)disp_val[0]);
	ft_putstr(" possibilities? (y or n)\n");
	signal(SIGINT, ft_sigint_completion);
}

int				ask_to_show_data(float *disp_val)
{
	FT_INIT(int, max_elem_lst, disp_val[5]);
	FT_INIT(int, elem_lst, disp_val[4]);
	FT_INIT(char*, c, g_shell.c);
	FT_INIT(int, situation, 0);
	ft_putendl("");
	if (max_elem_lst < elem_lst)
	{
		print_choice(disp_val);
		while (readkey() && !situation)
		{
			c = g_shell.c;
			if (c[0] == 89 || c[0] == 121)
				break ;
			else if (c[0] == 78 || c[0] == 110)
			{
				ft_putendl("");
				tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
				free(disp_val);
				signal(SIGINT, ft_sigint);
				return (0);
			}
		}
		disp_val[4] = max_elem_lst;
	}
	return (1);
}

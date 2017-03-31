/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_completion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/23 18:08:06 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

static	int		if_col(t_file *col, char *tmp,
								int len_str, t_completion *all_col)
{
	FT_INIT(int, nb_elem, 0);
	FT_INIT(t_file *, tmp_col, NULL);
	if (col)
	{
		tmp = set_sentence(tmp, len_str, col->name);
		tmp_col = col;
		col = col->next;
		ft_strdel(&(tmp_col)->name);
		ft_strdel(&(tmp_col)->absolute_path);
		free(tmp_col);
		all_col->elem = col;
		nb_elem--;
	}
	return (nb_elem);
}

static void		display_form(t_completion *all_col, int nb_elem,
					int len_str, int nb_col)
{
	FT_INIT(t_file *, col, all_col->elem);
	FT_INIT(t_completion *, head, all_col);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(int, ref_col, 0);
	tmp = ft_strnew(ft_strlen(col->name) + 4096);
	while (all_col && nb_elem)
	{
		head = !ref_col ? all_col : head;
		col = all_col->elem;
		nb_elem += if_col(col, tmp, len_str, all_col);
		if (ref_col >= nb_col - 1)
		{
			ft_putendl("");
			ref_col = 0;
			all_col = head;
		}
		else
			all_col = change_col(all_col, head, &ref_col, nb_elem);
	}
	ft_strdel(&tmp);
	ft_putendl("");
}

static void		ajust_final_positon(void)
{
	FT_INIT(int, go_down, g_shell.line_2d_y);
	while (go_down-- > 0)
		ft_putstr("\n");
	go_down = 0;
	while (go_down++ < g_shell.line_2d_y)
		tputs(tgetstr("up", NULL), 1, ft_putchar_int);
	tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
}

void			display_completion(char *sentence, t_file *match_files)
{
	if (!sentence || !match_files)
		return ;
	if (match_files->nb_elem == 1)
	{
		fill_current_line(' ');
		g_shell.cursor_x++;
		free_lists(match_files);
		return ;
	}
	FT_INIT(float*, disp_val, get_display_values(match_files));
	FT_INIT(t_completion *, lst_lst, NULL);
	FT_INIT(t_completion*, tmp_lst, NULL);
	FT_INIT(float, nb_col, disp_val[2]);
	FT_INIT(float, nb_elem_lst, disp_val[4]);
	if (!ask_to_show_data(disp_val))
		return (free_lists(match_files));
	signal(SIGINT, ft_sigint);
	lst_lst = build_lst_lst(match_files, (nb_elem_lst == 0 ?
			1 : nb_elem_lst), nb_col);
	tmp_lst = lst_lst;
	display_form(lst_lst, disp_val[0], disp_val[1], disp_val[2]);
	ajust_final_positon();
	free(disp_val);
	free_lst_lst(tmp_lst);
}

#include "../includes/42sh.h"

static int 		if_col(t_file *col, t_file *tmp_col, char *tmp, 
								int len_str, t_completion *all_col)
{
	if (col)
	{
		tmp = set_sentence(tmp, len_str, col->name);
		tmp_col = col;
		col = col->next;

		ft_strdel(&(tmp_col)->name);
		ft_strdel(&(tmp_col)->absolute_path);
		free(tmp_col);

		all_col->elem = col;
		return (-1);
	}
	return (0);
}

static void		display_form(t_completion *all_col, int nb_elem,
					int len_str, int nb_col)
{
	FT_INIT(t_file *, col, all_col->elem);
	FT_INIT(t_file *, tmp_col, col);
	FT_INIT(t_completion *, head, all_col);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(int, ref_col, 0);
	tmp = ft_strnew(ft_strlen(col->name) + 4096);
	while (all_col && nb_elem)
	{
		head = !ref_col ? all_col : head;
		col = all_col->elem;
		nb_elem += if_col(col, tmp_col, tmp, len_str, all_col);
		if (ref_col >= nb_col - 1)
		{
			ft_putendl("");
			ref_col = 0;
			all_col = head;
		}
		else
		{
			ref_col++;
			all_col = all_col->next;
		}
	}
	ft_strdel(&tmp);
}

static float 			*get_display_values(t_file *match_files)
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

static int 				ask_to_show_data(float *disp_val)
{
	FT_INIT(int, max_elem_lst, disp_val[5]);
	FT_INIT(int, elem_lst, disp_val[4]);
	FT_INIT(char*, c, g_shell.c);
	FT_INIT(int, situation, 0);
	ft_putendl("");
	if (max_elem_lst < elem_lst)
	{
		ft_printf("Display all %d possibilities? (y or n)", (int)disp_val[0]);
		while (readkey() && !situation)
		{
			c = g_shell.c;
			if (c[0] == 89 || c[0] == 121) // YES
				break ;
			else if (c[0] == 78 || c[0] == 110) // NO
			{
				ft_putendl("");
				tputs(tgetstr("sc", NULL), 1, ft_putchar_int);				
				return (0);
			}
		}
		disp_val[4] = max_elem_lst;
	}
	return (1);
}

void 			display_completion(char *sentence, t_file *match_files)
{
	if (!sentence || !match_files)
		return ;
	FT_INIT(float*, disp_val, get_display_values(match_files));
	FT_INIT(t_completion *, lst_lst, NULL);
	FT_INIT(t_completion*, tmp_lst, NULL);
	FT_INIT(float, nb_elem, disp_val[0]);
	FT_INIT(float, len_str, disp_val[1]);
	FT_INIT(float, nb_col, disp_val[2]);
	FT_INIT(float, nb_line, disp_val[3]);
	FT_INIT(float, nb_elem_lst, disp_val[4]);
	if (!ask_to_show_data(disp_val))
		return (free(disp_val));
	lst_lst = build_lst_lst(match_files, (nb_elem_lst == 0 ? 
				1 : nb_elem_lst), nb_col);
	tmp_lst = lst_lst;
	display_form(lst_lst, disp_val[0], disp_val[1], disp_val[2]);
	ft_putendl("");
	tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
	free(disp_val);
	free_lst_lst(tmp_lst);
	if (nb_elem || len_str || nb_col || nb_line || nb_elem_lst || lst_lst)
		return ;
}
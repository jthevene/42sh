/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:53:52 by jules             #+#    #+#             */
/*   Updated: 2017/02/03 09:55:33 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

int		check_hist_opt(void)
{
	int		options;

	options = -1;
	if (g_shell.hist_opt.a)
		options++;
	if (g_shell.hist_opt.r)
		options++;
	if (g_shell.hist_opt.w)
		options++;
	if (g_shell.hist_opt.p)
		options++;
	if (g_shell.hist_opt.s)
		options++;
	if (g_shell.hist_opt.d)
		options++;
	if (options)
		ft_putendl("cannot use more than one of -adrspw");
	return (options);
}

void	history_hub(char *line)
{
	split_line(line);
	get_history_options();
	FT_INIT(int, options, check_hist_opt());
	if (options > 0)
		return ;
	else if (options < 0 && !g_shell.hist_opt.c)
		ft_history(g_shell.hist_opt.filename);
	if (g_shell.hist_opt.c)
		clear_history_list();
	if (g_shell.hist_opt.d)
		delete_line_history(ft_atoi(g_shell.hist_opt.filename));
	else if (g_shell.hist_opt.a)
		update_history_file(g_shell.hist_opt.filename, \
				get_histsize("HISTSIZE"));
	else if (g_shell.hist_opt.r)
		histfile_append(g_shell.hist_opt.filename);
	else if (g_shell.hist_opt.w)
		update_history_file(g_shell.hist_opt.filename, \
				get_histsize("HISTSIZE"));
	else if (g_shell.hist_opt.s)
		ft_newhist(g_shell.hist_opt.arg);
}

void	ft_history_print(t_lst *lst)
{
	int		space;

	space = 5 - ft_nbrlen(lst->number);
	while (space-- > 0)
		ft_putchar(' ');
	ft_putstr(ft_itoa(lst->number));
	ft_putchar(' ');
	ft_putendl(lst->content);
}

void	ft_history(char *nbr)
{
	FT_INIT(int, i, 0);
	FT_INIT(t_lst *, tmp, g_shell.hist);
	if (!nbr)
		i = get_histsize("HISTSIZE");
	else
		i = ft_atoi(nbr);
	if (nbr && !ft_strisnum(nbr))
	{
		ft_putstr(nbr);
		ft_putendl(" : numeric argument required");
		return ;
	}
	if (g_shell.hist)
	{
		if (i > 0)
		{
			while (--i > 0 && tmp->prev)
				tmp = tmp->prev;
			while (tmp)
			{
				ft_history_print(tmp);
				tmp = tmp->next;
			}
		}
	}
}

void	show_hist_list()
{
	t_lst	*tmp;

	tmp = g_shell.hist;
	if (!tmp)
	{
		ft_putendl("LISTE VIDE");
		return ;
	}
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	ft_putendl("---LISTE HISTORY---");
	while (tmp)
	{
		if (tmp == g_shell.end_hist_file)
			ft_putchar('*');
		ft_putnbr(tmp->number);
		ft_putstr("=> ");
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
	ft_putendl("--------FIN--------");
}
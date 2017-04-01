/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/01 13:09:17 by jules            ###   ########.fr       */
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
	if (options > 0)
		ft_putendl_fd("cannot use more than one of -adrspw", 2);
	return (options);
}

int		history_hub(char *line)
{
	split_line(line);
	get_history_options();
	FT_INIT(int, options, check_hist_opt());
	if (options > 0 || invalid_option())
		return (1);
	if (options < 0 && !g_shell.hist_opt.c)
		ft_history(g_shell.hist_opt.filename);
	if (g_shell.hist_opt.c)
		clear_history_list();
	if (g_shell.hist_opt.d)
		delete_line_history(g_shell.hist_opt.filename);
	else if (g_shell.hist_opt.a)
		update_history_file(get_histsize("HISTSIZE"));
	else if (g_shell.hist_opt.r)
		histfile_append();
	else if (g_shell.hist_opt.w)
		update_history_file(get_histsize("HISTSIZE"));
	else if (g_shell.hist_opt.s && g_shell.hist_opt.arg)
		ft_newhist(g_shell.hist_opt.arg);
	return (1);
}

void	ft_history_print(t_lst *lst)
{
	int		space;
	char	*nbr;

	nbr = ft_itoa(lst->number);
	space = 5 - ft_nbrlen(lst->number);
	while (space-- > 0)
		ft_putchar(' ');
	ft_putstr(nbr);
	ft_putchar(' ');
	ft_putendl(lst->content);
	if (nbr)
		free(nbr);
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
		ft_putstr_fd(nbr, 2);
		ft_putendl_fd(" : numeric argument required", 2);
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

void	show_hist_list(void)
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

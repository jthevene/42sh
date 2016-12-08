/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:55:54 by jules             #+#    #+#             */
/*   Updated: 2016/12/05 10:48:50 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

// history -c
void	clear_history_list()
{
	if (g_shell.hist != NULL)
	{
		while (g_shell.hist->prev != NULL)
		{
			free(g_shell.hist->content);
			free(g_shell.hist);
			g_shell.hist = g_shell.hist->prev;
		}
		free(g_shell.hist->content);
		free(g_shell.hist);
		g_shell.hist = NULL;
	}
	init_hist();
}

// history -d
void	delete_line_history(int i)
{
	t_lst 	*tmp;

	tmp = g_shell.hist;
	if (i < 1 || i > g_shell.last_hist->number)
	{
		ft_putstr("history: ");
		ft_putnbr(i);
		ft_putstr(": history position out of range");
		return ;
	}
	if (tmp)
	{
		while (tmp->number > i)
			tmp = tmp->prev;
		free(tmp->content);
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		free(tmp);
		while (tmp != g_shell.hist)
		{
			tmp = tmp->next;
			tmp->number = i++;
		}
	}
}

void	show_hist_list()
{
	t_lst	*tmp;

	tmp = g_shell.hist;
	if (!tmp->content)
	{
		ft_putendl("LISTE VIDE");
		return ;
	}
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	ft_putendl("---LISTE HISTORY---");
	while (tmp->next)
	{
		if (tmp == g_shell.end_hist_file)
			ft_putchar('*');
		ft_putnbr(tmp->number);
		ft_putstr("=> ");
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
		if (tmp == g_shell.end_hist_file)
			ft_putchar('*');
	ft_putnbr(tmp->number);
	ft_putstr("=> ");
	ft_putendl(tmp->content);
	ft_putendl("--------FIN--------");
}

void	update_history_file()
{
//	char	*line;
	char	*filename;
	t_lst	*tmp;


	tmp = g_shell.hist;
//	line = NULL;
	filename = ft_strjoin(get_var(&g_shell, "HOME"), "/.history");
	g_shell.hist_fd = open(filename, O_RDWR | O_APPEND, 0600);
	while (tmp != g_shell.end_hist_file)
		tmp = tmp->prev;
	while (tmp->next)
	{
		tmp = tmp->next;
		ft_putendl_fd(tmp->content, g_shell.hist_fd);
	}
	close(g_shell.hist_fd);
}
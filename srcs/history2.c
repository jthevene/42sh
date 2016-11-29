/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:55:54 by jules             #+#    #+#             */
/*   Updated: 2016/11/29 10:28:25 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	delete_all_hist()
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
	{
		tmp = tmp->prev;
	}
	ft_putendl("LISTE HISTORY");
	ft_putendl("_ _ _ _ _ _ _ _ _ _ _ _ _ _");
	while (tmp->next)
	{
		ft_putnbr(tmp->number);
		ft_putstr("=> ");
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
	ft_putnbr(tmp->number);
	ft_putstr("=> ");
	ft_putendl(tmp->content);
	ft_putendl("_ _ _ _ _ _ _ _ _ _ _ _ _ _");
	ft_putendl("FIN");
}

// void	hist_r_option()
// {
// 	char	*filename;

// 	filename = ft_strjoin(get_var(&g_shell, "HOME"), "/.history");
// 	g_shell.hist_fd = open(filename, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0600);
// 	while (get_next_line(g_shell.hist_fd, ))
// 	{
		
// 	}
// 	close(g_shell.hist_fd);
// }

void	update_history_file()
{
	char	*line;
	char	*filename;

	FT_INIT(int, ret, 0);
	line = NULL;
	filename = ft_strjoin(get_var(&g_shell, "HOME"), "/.history");
	g_shell.hist_fd = open(filename, O_RDWR | O_APPEND, 0600);
	while ((ret = get_next_line(g_shell.hist_fd, &line)) == 1)
	{
		if (line)
			ft_putendl(line);
	}
	ft_putendl("-----FIN-----");
	close(g_shell.hist_fd);
}
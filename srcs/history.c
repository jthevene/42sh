/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:53:52 by jules             #+#    #+#             */
/*   Updated: 2016/11/25 16:49:24 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	init_hist()
{
	char	*filename;

	g_shell.hist_fd = 0;
	if (!(g_shell.hist = (t_lst*)malloc(sizeof(t_list))))
	{
		ft_putstr("g_shell.hist malloc failed");
		ft_reset_termios(g_shell.t_back);
		exit(0);
	}
	g_shell.hist->content = NULL;
	g_shell.hist->number = 0;
	g_shell.nav_hist = 0;
	g_shell.hist->next = NULL;
	g_shell.hist->prev = NULL;
	g_shell.last_hist = NULL;
	// g_shell.hist->last = (t_lst *)malloc(sizeof(t_lst));
	filename = ft_strjoin(get_var(&g_shell, "HOME"), "/.history");
	g_shell.hist_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	close(g_shell.hist_fd);
}

void	ft_newhist(char *line)
{
	t_lst	*new_hist;
	
	new_hist = (t_lst *)malloc(sizeof(t_lst));
	if (new_hist)
	{
		while (g_shell.hist->next)
			g_shell.hist = g_shell.hist->next;
		new_hist->content = ft_strdup(line);
		new_hist->next = NULL;
		new_hist->number = g_shell.hist->number + 1;
		new_hist->prev = g_shell.hist;
		g_shell.hist->next = new_hist;
		g_shell.last_hist = new_hist;
		g_shell.hist = new_hist;
	}
}

static void		put_hist_line(char *content)
{
	clean_line();
	display_prompt();
	ft_putstr(content);
}

//affiche la ligne suivante ou precedente de l'historique
void	navigation_hist(int arrow)
{
	if (g_shell.hist->content)
	{
		if (arrow == K_UP)
		{	
			if (g_shell.hist->prev->content)
			{
				if (g_shell.nav_hist == 0)
					g_shell.hist = g_shell.hist->prev;
				g_shell.nav_hist = 1;
				put_hist_line(g_shell.hist->content);
				g_shell.current_line = ft_strdup(g_shell.hist->content);
			}
		}
		else
		{
			if (g_shell.hist->next)
			{
				g_shell.hist = g_shell.hist->next;
				put_hist_line(g_shell.hist->content);
				g_shell.current_line = ft_strdup(g_shell.hist->content);
			}
		}
	}
}

void	ft_history(int i)
{
	t_lst 	*tmp;
	int 	space;

	space = 0;
	tmp = g_shell.hist;
	if (g_shell.hist->content)
	{
		if (i == 0)
			i++;
		else if (i > g_shell.hist->number)
			i = g_shell.hist->number;
		if (i > 0)
		{
			while (i-- > 0)
			{
				space = 5 - ft_nbrlen(tmp->number);
				while (space-- > 0)
					ft_putchar(' ');
				ft_putstr(ft_itoa(tmp->number));
				ft_putchar(' ');
				ft_putendl(tmp->content);
				tmp = tmp->prev;
			}
		}
	}
}
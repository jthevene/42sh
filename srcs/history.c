/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:53:52 by jules             #+#    #+#             */
/*   Updated: 2016/12/05 10:54:58 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	get_hist(void)
{
	char	*line;
	char	*filename;

	FT_INIT(int, ret, 0);
	line = NULL;
	filename = ft_strjoin(get_var(&g_shell, "HOME"), "/.history");
	g_shell.hist_fd = open(filename, O_RDWR, 0600);
	while ((ret = get_next_line(g_shell.hist_fd, &line)) == 1)
		ft_newhist(line);
	g_shell.end_hist_file = g_shell.hist;
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
		if (g_shell.hist->content)
		{
			new_hist->prev = g_shell.hist;
			g_shell.hist->next = new_hist;
		}
		else
		{
			g_shell.hist = new_hist;
			new_hist->prev = NULL;
		}
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
			if (g_shell.hist->prev && g_shell.hist->prev->content)
			{
				if (g_shell.nav_hist == 1) //nav_hist est remis à 0 quand la touche return est pressée
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
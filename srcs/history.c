/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:53:52 by jules             #+#    #+#             */
/*   Updated: 2016/11/21 16:46:42 by jules            ###   ########.fr       */
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
	g_shell.hist->next = NULL;
	g_shell.hist->prev = NULL;
	g_shell.hist->last = NULL;
	filename = ft_strjoin(get_var(&g_shell, "HOME"), "/.history");
	g_shell.hist_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);//penser à close
}

void	ft_newhist(char *line)
{
	t_lst	*new_hist;
	
	new_hist = (t_lst *)malloc(sizeof(t_lst));
	if (new_hist)
	{
		new_hist->content = ft_strdup(line);
		new_hist->next = NULL;
		new_hist->number = g_shell.hist->number + 1;
		new_hist->prev = g_shell.hist;
		g_shell.hist->next = new_hist;
		g_shell.hist->last = new_hist;
		g_shell.hist = new_hist;
	}
	write(g_shell.hist_fd, ft_itoa(g_shell.hist->number), ft_nbrlen(g_shell.hist->number));
	write(g_shell.hist_fd, " ", 1);
	write(g_shell.hist_fd, line, ft_strlen(line));
	write(g_shell.hist_fd, "\n", 1);
}

static void		put_hist_line(char *content)
{
	clean_line();
	display_prompt();
	ft_putstr(content);
}

//affiche la ligne suivante ou precedente de l'historique
void	nav_hist(int arrow)
{
	static int 		last_elem = 1;

	if (g_shell.hist->content)
	{
		if (arrow == K_UP)
		{	
			if (g_shell.hist->prev->content)
			{
				if (last_elem == 0)
					g_shell.hist = g_shell.hist->prev;
				last_elem = 0;
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

	tmp = g_shell.hist;
	if (i == 0)
		i++;
	if (i > 0)
	{
		while (i-- > 0)
		{
			ft_putstr(ft_itoa(tmp->number));
			ft_putchar(' ');
			ft_putendl(tmp->content);
			tmp = tmp->prev;
		}
	}
}
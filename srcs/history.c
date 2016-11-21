/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 11:53:52 by jules             #+#    #+#             */
/*   Updated: 2016/11/18 13:52:14 by jules            ###   ########.fr       */
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
		new_hist->prev = g_shell.hist;
		g_shell.hist->next = new_hist;
		g_shell.hist->last = new_hist;
		g_shell.hist = new_hist;
	}
	write(g_shell.hist_fd, line, ft_strlen(line));
	write(g_shell.hist_fd, "\n", 1);
}

void	nav_hist(int arrow)
{
	static int 		last_elem = 1;

	if (arrow == K_UP)
	{	
		if (g_shell.hist->prev->content)
		{
			if (last_elem == 0)
				g_shell.hist = g_shell.hist->prev;
			last_elem = 0;
			clean_line();
			display_prompt();
			ft_putstr(g_shell.hist->content);
			g_shell.current_line = ft_strdup(g_shell.hist->content);
		}
	}
	else
	{
		if (g_shell.hist->next)
		{
			g_shell.hist = g_shell.hist->next;
			clean_line();
			display_prompt();
			ft_putstr(g_shell.hist->content);
			g_shell.current_line = ft_strdup(g_shell.hist->content);
		}
	}
}
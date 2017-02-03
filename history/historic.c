/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 10:57:09 by jules             #+#    #+#             */
/*   Updated: 2017/02/03 09:49:48 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

void	get_hist(void)
{
	FT_INIT(char *, filename, NULL);
	FT_INIT(char *, line, NULL);
	FT_INIT(int, ret, 0);
	filename = ft_strjoin(get_var(&g_shell, "HOME"), "/.history");
	if ((g_shell.hist_fd = open(filename, O_RDWR, 0600)) == -1)
	{
		ft_error(filename);
		free(filename);
		return ;
	}
	while (((ret = get_next_line(g_shell.hist_fd, &line)) == 1))
	{
		ft_newhist(line);
		free(line);
	}
	g_shell.end_hist_file = g_shell.hist;
	free(filename);
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
		if (g_shell.hist == NULL)
			new_hist->number = 1;
		else
		{
			g_shell.hist->next = new_hist;
			new_hist->number = g_shell.hist->number + 1;
		}
		g_shell.hist = new_hist;
	}
	update_histsize(get_histsize("HISTSIZE"));
}

void	put_hist_line(char *content)
{
	clean_line();
	display_prompt();
	ft_putstr(content);
}

void	navigation_hist(int arrow)
{
	if (g_shell.curr_hist)
	{
		if (arrow == K_UP)
		{
			if (g_shell.curr_hist->prev && g_shell.curr_hist->prev->content)
			{
				if (g_shell.nav_hist == 1)
					g_shell.curr_hist = g_shell.curr_hist->prev;
				g_shell.nav_hist = 1;
				put_hist_line(g_shell.curr_hist->content);
				g_shell.current_line = ft_strdup(g_shell.curr_hist->content);
			}
		}
		else
		{
			if (g_shell.curr_hist->next)
			{
				g_shell.curr_hist = g_shell.curr_hist->next;
				put_hist_line(g_shell.curr_hist->content);
				g_shell.current_line = ft_strdup(g_shell.curr_hist->content);
			}
		}
		g_shell.cursor_x = ft_strlen(g_shell.current_line)
			+ g_shell.prompt_len;
	}
}

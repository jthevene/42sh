/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvirgile <dvirgile@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/10 17:02:03 by dvirgile         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

void	free_hist(void)
{
	if (g_shell.hist)
	{
		while (g_shell.hist->prev)
		{
			free(g_shell.hist->content);
			g_shell.hist = g_shell.hist->prev;
		}
		free(g_shell.hist->content);
		g_shell.hist = g_shell.hist->prev;
		g_shell.hist = NULL;
		free(g_shell.hist);
	}
}

void	get_hist(void)
{
	FT_INIT(char *, filename, NULL);
	FT_INIT(char *, line, NULL);
	FT_INIT(char*, home, get_var(g_shell.env, "HOME"));
	FT_INIT(int, ret, 0);
	filename = ft_strjoin(home, "/.history");
	free(home);
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
	if (line)
		free(line);
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
	if (!((int)ft_strlen(content)))
	{
		tputs(tgetstr("rc", NULL), 1, ft_putchar_int);
		tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
		tputs(tgetstr("cd", NULL), 1, ft_putchar_int);
		tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
		ft_putstr(g_shell.prompt);
		ft_putstr(content);
	}
}

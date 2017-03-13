/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/13 12:39:01 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/history.h"

void	get_history_options(void)
{
	if (!g_shell.hist_opt.options)
		return ;
	if (ft_strchr(g_shell.hist_opt.options, 'c'))
		g_shell.hist_opt.c = true;
	if (ft_strchr(g_shell.hist_opt.options, 'd'))
		g_shell.hist_opt.d = true;
	if (ft_strchr(g_shell.hist_opt.options, 'a'))
		g_shell.hist_opt.a = true;
	if (ft_strchr(g_shell.hist_opt.options, 'r'))
		g_shell.hist_opt.r = true;
	if (ft_strchr(g_shell.hist_opt.options, 'w'))
		g_shell.hist_opt.w = true;
	if (ft_strchr(g_shell.hist_opt.options, 'p'))
		g_shell.hist_opt.p = true;
	if (ft_strchr(g_shell.hist_opt.options, 's'))
		g_shell.hist_opt.s = true;
}

void	clear_history_list(void)
{
	FT_INIT(t_lst *, tmp, NULL);
	while (g_shell.hist != NULL)
	{
		tmp = g_shell.hist;
		if (g_shell.hist->content)
			free(g_shell.hist->content);
		g_shell.hist = g_shell.hist->prev;
		free(tmp);
	}
	g_shell.hist = NULL;
	g_shell.nav_hist = 0;
	g_shell.curr_hist = NULL;
}

void	delete_line_history(char *nbr)
{
	FT_INIT(t_lst *, tmp, g_shell.hist);
	if (!nbr)
	{
		ft_putendl_fd("history -d argument must be a positive number", 2);
		return ;
	}
	FT_INIT(int, i, ft_atoi(nbr));
	if (!tmp || i < 1 || i > tmp->number)
	{
		ft_out_of_range(i);
		return ;
	}
	while (tmp->number > i)
	{
		tmp->number--;
		tmp = tmp->prev;
	}
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (g_shell.hist == tmp)
		g_shell.hist = tmp->prev;
	free(tmp->content);
	free(tmp);
}

void	update_history_file(int histfilesize)
{
	FT_INIT(t_lst *, tmp, g_shell.hist);
	FT_INIT(int, i, 0);
	FT_INIT(char *, histfile, get_var(g_shell.env, "HOME"));
	if (!tmp)
		return ;
	if (!g_shell.hist_opt.filename)
		g_shell.hist_opt.filename = ft_strjoin(histfile, "/.history");
	if (histfile)
		free(histfile);
	if ((g_shell.hist_fd = open(g_shell.hist_opt.filename, O_RDWR | O_CREAT |
	O_TRUNC, 0600)) == -1)
		return (ft_error(g_shell.hist_opt.filename));
	while (i < histfilesize && i < get_histsize("HISTSIZE") && tmp->prev)
	{
		i++;
		tmp = tmp->prev;
	}
	while (tmp)
	{
		ft_putendl_fd(tmp->content, g_shell.hist_fd);
		tmp = tmp->next;
	}
	close(g_shell.hist_fd);
}

void	histfile_append(void)
{
	FT_INIT(int, ret, 0);
	FT_INIT(char *, line, NULL);
	FT_INIT(char *, home, get_var(g_shell.env, "HOME"));
	if (!g_shell.hist_opt.filename)
		g_shell.hist_opt.filename = ft_strjoin(home, "/.history");
	if (home)
		free(home);
	if ((g_shell.hist_fd = open(g_shell.hist_opt.filename, O_RDONLY, 0600))
	== -1)
		return (ft_error(g_shell.hist_opt.filename));
	while (((ret = get_next_line(g_shell.hist_fd, &line)) == 1))
	{
		ft_newhist(line);
		free(line);
	}
	if (line)
		free(line);
}

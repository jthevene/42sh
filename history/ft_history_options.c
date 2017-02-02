/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:55:54 by jules             #+#    #+#             */
/*   Updated: 2017/02/02 21:11:12 by jules            ###   ########.fr       */
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
	while (g_shell.hist != NULL)
	{
		free(g_shell.hist->content);
		free(g_shell.hist);
		g_shell.hist = g_shell.hist->prev;
	}
	init_hist();
}

void	delete_line_history(int i)
{
	t_lst	*tmp;

	tmp = g_shell.hist;
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
}

void	update_history_file(char *filename, int histfilesize)
{
	FT_INIT(t_lst *, tmp, g_shell.hist);
	FT_INIT(int, i, 0);
	if (!tmp)
		return ;
	if (!filename)
		filename = ft_strjoin(get_var(&g_shell, "HOME"), "/.history");
	if ((g_shell.hist_fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0600)) \
		== -1)
	{
		ft_error(filename);
		return ;
	}
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
	free(filename);
}

void	histfile_append(char *filename)
{
	FT_INIT(int, ret, 0);
	FT_INIT(char *, line, NULL);
	if (!filename)
		filename = ft_strjoin(get_var(&g_shell, "HOME"), "/.history");
	if ((g_shell.hist_fd = open(filename, O_RDONLY, 0600)) == -1)
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
	free(filename);
}

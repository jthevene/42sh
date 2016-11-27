/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 16:55:54 by jules             #+#    #+#             */
/*   Updated: 2016/11/27 11:22:50 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "42sh.h"

void	delete_all_hist()
{
	if (g_shell.hist != NULL && *g_shell.hist != NULL)
	{
		while (g_shell.hist->prev != NULL)
		{
			free(g_shell.hist->content);
			free(*g_shell.hist);
			*g_shell.hist = (*g_shell.hist)->prev;
		}
		free(g_shell.hist->content);
		free(*g_shell.hist);
		*g_shell.hist = NULL;
	}
	init_hist()
}

// history -d
void	delete_line_history(int i)
{
	t_lst 	*tmp;

	tmp = g_shell.hist;
	if (tmp != NULL)
	{
		while (tmp->number > i)
			tmp = tmp->prev;
		free(tmp->content);
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		free(tmp)
		while (tmp != g_shell.hist)
		{
			tmp = tmp->next;
			tmp->number = i++;
		}
	}
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
	char	*filename;

	filename = ft_strjoin(get_var(&g_shell, "HOME"), "/.history");
	g_shell.hist_fd = open(filename, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0600);
	
	close(g_shell.hist_fd);
}
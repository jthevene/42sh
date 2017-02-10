/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 09:24:08 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/10 09:24:09 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/42sh.h"

/*
static int		detect_out(void)
{
	FT_INIT(int, i, 0);
	while (g_shell.line[i] && g_shell.line[i] != '>')
		i++;
	if (g_shell.line[i - 1] != ' ' && ft_isdigit(g_shell.line[i - 1]))
		return (g_shell.line[i - 1] - 48);
	else
		return (1);
}
*/

static int		exec_redir(t_tree *left, int fd_out, t_fdlist *fdlist)
{
	while (fdlist->next)
		fdlist = fdlist->next;
	g_shell.redir_fd = fdlist->key;
	g_shell.redir_fd_out = fd_out;
	return (exec_function(left->content));
}

static int		create_file(char *filename, t_fdlist **fdlist, int type)
{
	int			fd;

	if (type == SIMPLE)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (0);
	if (!(*fdlist))
		fdlist_pushback(&(*fdlist), 0);
	if (!fdlist_pushback(&(*fdlist), fd))
		return (0);
	return (fd);
}

static int		get_filename(t_tree *r, t_fdlist **fdl, int type) 
{
	FT_INIT(int, ret, 0);
	ret = create_file(r->content, fdl, type == MORE ? SIMPLE : DOUBLE);
	if (!ret)
		return (0);
	if (r->type != MORE && r->type != DMORE)
		return (1);
	return (get_filename(r->right, fdl, r->type));
}

int				run_redir(t_tree *left, t_tree *right, int current_type)
{
	FT_INIT(int, fd_out, 0);
	FT_INIT(t_fdlist, *fdlist, NULL);
	fd_out = 1; /*detect_out();*/
	if (!(get_filename(right, &fdlist, current_type)))
		return (0);
	if (!(exec_redir(left, fd_out, fdlist)))
		return (0);
	free_fdlist(&fdlist);
	g_shell.redir_fd = 0;
	g_shell.redir_fd_out = 0;
	return (1);
}

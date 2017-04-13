/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/13 10:37:13 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

void			handle_aggreg(t_save_fd **save_list, int is_builtin)
{
	if (g_shell.aggreg != NULL)
	{
		while (g_shell.aggreg->prev)
			g_shell.aggreg = g_shell.aggreg->prev;
		while (g_shell.aggreg->next)
		{
			if (is_builtin == IS_BUILTIN)
				go_save_fd(&(*save_list), g_shell.aggreg->fd_in);
			if (g_shell.aggreg->fd_file == -1)
				close(get_fd_to_close(g_shell.aggreg->fd_in));
			else
				dup2(g_shell.aggreg->fd_file, g_shell.aggreg->fd_in);
			g_shell.aggreg = g_shell.aggreg->next;
		}
		if (is_builtin == IS_BUILTIN)
			go_save_fd(&(*save_list), g_shell.aggreg->fd_in);
		if (g_shell.aggreg->fd_file == -1)
			close(get_fd_to_close(g_shell.aggreg->fd_in));
		else
			dup2(g_shell.aggreg->fd_file, g_shell.aggreg->fd_in);
	}
}

static void		handle_left_redir(int is_builtin)
{
	if (is_builtin == IS_BUILTIN)
		go_save_fd(&g_shell.save_list, STDIN_FILENO);
	dup2(g_shell.left_redir_fd, STDIN_FILENO);
	close(g_shell.left_redir_fd);
	g_shell.left_redir_fd = -1;
}

void			handle_redirections(int is_builtin)
{
	if (g_shell.right_redirs)
	{
		while (g_shell.right_redirs->prev)
			g_shell.right_redirs = g_shell.right_redirs->prev;
		while (g_shell.right_redirs->next)
		{
			if (is_builtin == IS_BUILTIN)
				go_save_fd(&g_shell.save_list, g_shell.right_redirs->fd_in);
			dup2(g_shell.right_redirs->fd_file, g_shell.right_redirs->fd_in);
			close(g_shell.right_redirs->fd_file);
			g_shell.right_redirs = g_shell.right_redirs->next;
		}
		if (is_builtin == IS_BUILTIN)
			go_save_fd(&g_shell.save_list, g_shell.right_redirs->fd_in);
		dup2(g_shell.right_redirs->fd_file, g_shell.right_redirs->fd_in);
		close(g_shell.right_redirs->fd_file);
	}
	handle_aggreg(&g_shell.save_list, is_builtin);
	if (g_shell.left_redir_fd != -1)
		handle_left_redir(is_builtin);
}

int				call_redirections(char **content)
{
	FT_INIT(char *, tmp, NULL);
	if (ft_strchr((*content), '<'))
	{
		tmp = hub_simple_left_redir(ft_strdup((*content)));
		if (!tmp)
			return (0);
		ft_strdel(&(*content));
		(*content) = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	if (ft_strstr((*content), ">&") || ft_strstr((*content), "<&"))
		hub_aggreg(&(*content));
	if (ft_strchr((*content), '>'))
	{
		tmp = hub_right_redir(ft_strdup((*content)));
		ft_strdel(&(*content));
		(*content) = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	return (1);
}

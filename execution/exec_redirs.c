/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apinho <apinho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 18:13:29 by apinho            #+#    #+#             */
/*   Updated: 2017/02/24 18:36:44 by apinho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

void		restablish_fd(t_save_fd **save_list)
{
	if (!save_list || !(*save_list))
		return ;
	if ((*save_list)->save_stdin != -1)
		dup2((*save_list)->save_stdin, STDIN_FILENO);
	if ((*save_list)->save_stdout != -1)
		dup2((*save_list)->save_stdout, STDOUT_FILENO);
	if ((*save_list)->save_stderr != -1)
		dup2((*save_list)->save_stderr, STDERR_FILENO);
	(*save_list)->save_stdin = -1;
	(*save_list)->save_stdout = -1;
	(*save_list)->save_stderr = -1;
	free_aggreg();
	free_right_redir();
}

static void	go_save_fd(t_save_fd **save_list, int fd_to_save)
{
	if (!save_list || !(*save_list))
		return ;
	if (fd_to_save == 0)
		(*save_list)->save_stdin = dup(STDIN_FILENO);
	if (fd_to_save == 1)
		(*save_list)->save_stdout = dup(STDOUT_FILENO);
	if (fd_to_save == 2)
		(*save_list)->save_stderr = dup(STDERR_FILENO);
}

void		handle_aggreg(t_save_fd **save_list, int is_builtin)
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

void		handle_redirections(int is_builtin)
{
	handle_aggreg(&g_shell.save_list, is_builtin);
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
	if (g_shell.left_redir_fd != -1)
	{
		dup2(g_shell.left_redir_fd, STDIN_FILENO);
		close(g_shell.left_redir_fd);
		g_shell.left_redir_fd = -1;
	}
}

void		call_redirections(char **content)
{
	FT_INIT(char *, tmp, NULL);
	if (ft_strstr((*content), ">&") || ft_strstr((*content), "<&"))
		hub_aggreg(&(*content));
	if (ft_strchr((*content), '<'))
	{
		tmp = hub_simple_left_redir(ft_strdup((*content)));
		ft_strdel(&(*content));
		(*content) = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	if (ft_strchr((*content), '>'))
	{
		tmp = hub_right_redir(ft_strdup((*content)));
		ft_strdel(&(*content));
		(*content) = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
}

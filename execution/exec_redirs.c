/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 17:21:26 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/18 17:21:27 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

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
	if (fd_to_save == 0)
		(*save_list)->save_stdin = dup(STDIN_FILENO);
	else
		(*save_list)->save_stdin = -1;
	if (fd_to_save == 1)
		(*save_list)->save_stdout = dup(STDOUT_FILENO);
	else
		(*save_list)->save_stdout = -1;
	if (fd_to_save == 2)
		(*save_list)->save_stderr = dup(STDERR_FILENO);
	else
		(*save_list)->save_stderr = -1;
}

void		handle_aggreg(t_save_fd **save_list)
{
	if (g_shell.aggreg != NULL)
	{
		while (g_shell.aggreg->prev)
			g_shell.aggreg = g_shell.aggreg->prev;
		while (g_shell.aggreg->next)
		{
			go_save_fd(&(*save_list), g_shell.aggreg->fd_in);
			if (g_shell.aggreg->fd_file == -1)
				close(g_shell.aggreg->fd_in);
			else
				dup2(g_shell.aggreg->fd_file, g_shell.aggreg->fd_in);
			g_shell.aggreg = g_shell.aggreg->next;
		}
		go_save_fd(&(*save_list), g_shell.aggreg->fd_in);
		if (g_shell.aggreg->fd_file == -1)
			close(g_shell.aggreg->fd_in);
		else
			dup2(g_shell.aggreg->fd_file, g_shell.aggreg->fd_in);
	}
}

void		handle_redirections(void)
{
	handle_aggreg(&g_shell.save_list);
	if (g_shell.right_redirs)
	{
		while (g_shell.right_redirs->prev)
			g_shell.right_redirs = g_shell.right_redirs->prev;
		while (g_shell.right_redirs->next)
		{
			go_save_fd(&g_shell.save_list, g_shell.right_redirs->fd_in);
			dup2(g_shell.right_redirs->fd_file, g_shell.right_redirs->fd_in);
			close(g_shell.right_redirs->fd_file);
			g_shell.right_redirs = g_shell.right_redirs->next;
		}
		go_save_fd(&g_shell.save_list, g_shell.right_redirs->fd_in);
		dup2(g_shell.right_redirs->fd_file, g_shell.right_redirs->fd_in);
		close(g_shell.right_redirs->fd_file);
	}
	if (g_shell.left_redir_fd)
	{
		dup2(g_shell.left_redir_fd, STDIN_FILENO);
		close(g_shell.left_redir_fd);
		g_shell.left_redir_fd = 0;
	}
}

void		call_redirections(char **content)
{
	FT_INIT(char *, tmp, NULL);
	if (ft_strstr((*content), ">&") || ft_strstr((*content), "<&"))
		hub_aggreg(&(*content));
	else if (ft_strchr((*content), '>'))
	{
		tmp = hub_right_redir(ft_strdup((*content)));
		ft_strdel(&(*content));
		(*content) = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	if (ft_strchr((*content), '<'))
	{
		tmp = hub_simple_left_redir(ft_strdup((*content)));
		ft_strdel(&(*content));
		(*content) = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
}
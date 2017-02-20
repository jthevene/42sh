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

void		go_save_fd(t_save_fd **save_fd, int fd_to_save)
{
	if (fd_to_save == 0)
		(*save_fd)->save_stdin = dup(STDIN_FILENO);
	if (fd_to_save == 1)
		(*save_fd)->save_stdout = dup(STDOUT_FILENO);
	if (fd_to_save == 2)
		(*save_fd)->save_stderr = dup(STDERR_FILENO);
}

void		handle_aggreg(t_save_fd **save_fd)
{
	if (g_shell.aggreg)
	{
		while (g_shell.aggreg->prev)
			g_shell.aggreg = g_shell.aggreg->prev;
		while (g_shell.aggreg->next)
		{
			if (g_shell.aggreg->fd_file == -1)
				close(g_shell.aggreg->fd_in);
			else
			{
				go_save_fd(&(*save_fd), g_shell.aggreg->fd_in);
				dup2(g_shell.aggreg->fd_in, g_shell.aggreg->fd_file);
			}
			g_shell.aggreg = g_shell.aggreg->next;
		}
		if (g_shell.aggreg->fd_file == -1)
			close(g_shell.aggreg->fd_in);
		else
		{
			go_save_fd(&(*save_fd), g_shell.aggreg->fd_in);
			dup2(g_shell.aggreg->fd_in, g_shell.aggreg->fd_file);
		}
	}
}

void		handle_redirections(void)
{
	FT_INIT(t_save_fd *, save_fd, (t_save_fd *)malloc(sizeof(t_save_fd)));
	handle_aggreg(&save_fd);
	if (g_shell.right_redirs)
	{
		while (g_shell.right_redirs->prev)
			g_shell.right_redirs = g_shell.right_redirs->prev;
		while (g_shell.right_redirs->next)
		{
			go_save_fd(&save_fd, g_shell.right_redirs->fd_in);
			dup2(g_shell.right_redirs->fd_file, g_shell.right_redirs->fd_in);
			close(g_shell.right_redirs->fd_file);
			g_shell.right_redirs = g_shell.right_redirs->next;
		}
		go_save_fd(&save_fd, g_shell.aggreg->fd_in);
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

int			verif_access_bin(char *path)
{
	struct stat infos;

	lstat(path, &infos);
	if (access(path, F_OK) != 0)
		return (0);
	return (1);
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
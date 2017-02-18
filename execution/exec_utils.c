/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 08:20:31 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/13 12:38:36 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

void		handle_redirections(void)
{
	if (g_shell.right_redirs)
	{
		while (g_shell.right_redirs->prev)
			g_shell.right_redirs = g_shell.right_redirs->prev;
		while (g_shell.right_redirs->next)
		{
			dup2(g_shell.right_redirs->fd_file, g_shell.right_redirs->fd_in);
			close(g_shell.right_redirs->fd_file);
			g_shell.right_redirs = g_shell.right_redirs->next;
		}
		if (dup2(g_shell.right_redirs->fd_file,
		g_shell.right_redirs->fd_in == 1 ? STDOUT_FILENO :
		FT_TER(g_shell.right_redirs->fd_in == 2, STDERR_FILENO,
		g_shell.right_redirs->fd_in)) == -1)
			return ;
		close(g_shell.right_redirs->fd_file);
	}
	if (g_shell.left_redir_fd)
	{
		dup2(g_shell.left_redir_fd, STDIN_FILENO);
		close(g_shell.left_redir_fd);
		g_shell.left_redir_fd = 0;
	}
}

int			verif_access_others(char *path)
{
	struct stat infos;

	lstat(path, &infos);
	if (access(path, F_OK) != 0)
		return (0);
	else if (access(path, X_OK) != 0 || !S_ISDIR(infos.st_mode))
		return (0);
	else if (!S_ISDIR(infos.st_mode))
		return (0);
	return (1);
}

char		**get_bin_directories(void)
{
	FT_INIT(char **, bin_directories, NULL);
	FT_INIT(char*, tmp, NULL);
	if (!g_shell.env)
		return (NULL);
	tmp = get_var(&g_shell, "PATH");
	if (!tmp)
		return (NULL);
	else
	{
		bin_directories = ft_strsplit(tmp, ':');
		free(tmp);
	}
	return (bin_directories);
}

char		**get_args(char *content)
{
	FT_INIT(char **, args, NULL);
	if (!content)
		return (NULL);
	if (ft_strchr(content, ' '))
		args = ft_strsplit(content, ' ');
	else
	{
		args = (char **)malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(content);
		args[1] = NULL;
	}
	return (args);
}

void		error_exec(char **args, char **cmd)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	ft_strdel(cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:46:30 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

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

void		go_save_fd(t_save_fd **save_list, int fd_to_save)
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

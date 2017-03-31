/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggreg_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:42 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:45:38 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

int			free_tmp_aggreg(t_fdlist **tmp)
{
	FT_INIT(t_fdlist *, inter, NULL);
	inter = g_shell.aggreg;
	g_shell.aggreg = *tmp;
	free_aggreg();
	g_shell.aggreg = inter;
	return (0);
}

int			start_aggreg(char **cmd, int *fd_in, int *fd_out, t_fdlist **tmp)
{
	while (ft_strstr((*cmd), ">&") || ft_strstr((*cmd), "<&"))
	{
		if (!detect_aggreg(&(*cmd), &(*fd_in), &(*fd_out)))
			return (0);
		if (!pushback_aggreg(&(*tmp), (*fd_in), (*fd_out)))
			return (0);
		FT_MULTI3((*fd_in), (*fd_out), 0);
	}
	return (1);
}

int			get_fd_to_close(int fd)
{
	if (fd == 0)
		return (STDIN_FILENO);
	else if (fd == 1)
		return (STDOUT_FILENO);
	else if (fd == 2)
		return (STDERR_FILENO);
	else
		return (fd);
}

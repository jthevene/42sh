/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggreg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 13:01:44 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/22 08:56:10 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

static int	detect_numbers(char *cmd, int i)
{
	FT_INIT(int, start, i);
	FT_INIT(char *, number, NULL);
	FT_INIT(int, ret, 0);
	while (cmd[i] && ft_isdigit(cmd[i]))
		i++;
	number = ft_strsub(cmd, start, i - start);
	ret = atoi(number);
	free(number ? number : NULL);
	return (ret);
}

static int	replace_cmd_aggreg(char **cmd, int i, int j)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	FT_INIT(char *, tmp_replace, NULL);
	while ((*cmd)[i] && (*cmd)[i + 1] && ft_isdigit((*cmd)[i]))
		i++;
	if ((*cmd)[i] && !ft_isdigit((*cmd)[i]) && (*cmd)[i] != '-')
		i--;
	tmp2 = ft_strdup((*cmd));
	ft_strdel(cmd);
	tmp = ft_strsub(tmp2, j, i - j + 1);
	tmp_replace = ft_str_replace(tmp2, tmp, "");
	(*cmd) = ft_strdup(tmp_replace);
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
	ft_strdel(&tmp_replace);
	return (1);
}

static int	detect_aggreg(char **cmd, int *fd_in, int *fd_out)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	while ((*cmd)[i])
	{
		if (((*cmd)[i] == '>' || (*cmd)[i] == '<') && (*cmd)[i + 1] && \
				(*cmd)[i + 1] == '&' && (*cmd)[i + 2]
			&& ((*cmd)[i + 2] == '-' || ft_isdigit((*cmd)[i + 2])))
		{
			if ((*cmd)[i - 1] && ft_isdigit((*cmd)[i - 1]))
			{
				j = i - 1;
				while ((*cmd)[j] && j >= 0 && ft_isdigit((*cmd)[j]))
					j--;
				(*fd_in) = detect_numbers((*cmd), ++j);
			}
			(*fd_in) = !(*fd_in) ? 1 : (*fd_in);
			(*fd_out) = ft_isdigit((*cmd)[i + 2]) ? detect_numbers((*cmd), \
					i + 2) : -1;
			return (replace_cmd_aggreg(&(*cmd), i + 2, j));
		}
		else if (((*cmd)[i] == '>' || (*cmd)[i] == '<') && (*cmd)[i + 1] && \
				(*cmd)[i + 1] == '&' && (*cmd)[i + 2]
			&& ((*cmd)[i + 2] != '-' || !ft_isdigit((*cmd)[i + 2])))
			return (0);
		i++;
	}
	return (1);
}

static int	pushback_aggreg(t_fdlist **flist, int fd_in, int fd_out)
{
	FT_INIT(t_fdlist *, new, NULL);
	FT_INIT(t_fdlist *, tmp, NULL);
	if (!(*flist))
	{
		if (!((*flist) = (t_fdlist *)malloc(sizeof(t_fdlist))))
			return (0);
		(*flist)->fd_in = fd_in;
		(*flist)->fd_file = fd_out;
		(*flist)->prev = NULL;
		(*flist)->next = NULL;
		return (1);
	}
	if (!(new = (t_fdlist *)malloc(sizeof(t_fdlist))))
		return (0);
	new->prev = NULL;
	new->next = NULL;
	new->fd_in = fd_in;
	new->fd_file = fd_out;
	while ((*flist)->next)
		(*flist) = (*flist)->next;
	tmp = (*flist);
	tmp->next = new;
	new->prev = tmp;
	return (1);
}

int 		free_tmp(t_fdlist **tmp)
{
	FT_INIT(t_fdlist *, inter, NULL);
	inter = g_shell.aggreg;
	g_shell.aggreg = *tmp;
	free_aggreg();
	g_shell.aggreg = inter;
	return (0);
}

int			hub_aggreg(char **cmd)
{
	FT_INIT(int, fd_in, 0);
	FT_INIT(int, fd_out, 0);
	FT_INIT(t_fdlist *, tmp, NULL);
	FT_INIT(t_fdlist *, tmp_start, NULL);
	while (ft_strstr((*cmd), ">&") || ft_strstr((*cmd), "<&"))
	{
		if (!detect_aggreg(&(*cmd), &fd_in, &fd_out))
			return (0);
		if (!pushback_aggreg(&tmp, fd_in, fd_out))
			return (0);
		fd_in = 0;
		fd_out = 0;
	}
	tmp_start = tmp;
	while (tmp->next)
		tmp = tmp->next;
	if (!pushback_aggreg(&g_shell.aggreg, tmp->fd_in, tmp->fd_file))
		return (free_tmp(&tmp_start));
	if (tmp->prev)
		tmp = tmp->prev;
	else
		return (free_tmp(&tmp_start));
	while (tmp)
	{
		if (!fd_already_in_fdlist(&g_shell.aggreg, tmp->fd_in))
			if (!pushback_aggreg(&g_shell.aggreg, tmp->fd_in, tmp->fd_file))
				return (free_tmp(&tmp_start));
		if (!tmp->prev)
			break ;
		tmp = tmp->prev;
	}
	free_tmp(&tmp_start);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggreg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 15:18:50 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:53 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

int			detect_numbers(char *cmd, int i)
{
	FT_INIT(int, start, i);
	FT_INIT(char *, number, NULL);
	FT_INIT(int, ret, 0);
	while (cmd[i] && ft_isdigit(cmd[i]))
		i++;
	number = ft_strsub(cmd, start, i - start);
	ret = ft_atoi(number);
	free(number ? number : NULL);
	return (ret);
}

int			replace_cmd_aggreg(char **cmd, int i, int j)
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

int			detect_aggreg(char **c, int *fd_in, int *out)
{
	FT_INIT(int, i, -1);
	FT_INIT(int, j, 0);
	while ((*c)[++i])
	{
		if (((*c)[i] == '>' || (*c)[i] == '<') && (*c)[i + 1] && \
			(*c)[i + 1] == '&' && (*c)[i + 2]
			&& ((*c)[i + 2] == '-' || ft_isdigit((*c)[i + 2])))
		{
			j = i - 1;
			if ((*c)[i - 1] && ft_isdigit((*c)[i - 1]))
			{
				while ((*c)[j] && j >= 0 && ft_isdigit((*c)[j]))
					j--;
				(*fd_in) = detect_numbers((*c), ++j);
			}
			(*fd_in) = !(*fd_in) ? FT_TER((*c)[i] == '>', 1, 0) : (*fd_in);
			(*out) = ft_isdigit((*c)[i + 2]) ? detect_numbers((*c), i + 2) : -1;
			return (replace_cmd_aggreg(&(*c), i + 2, j));
		}
		else if (((*c)[i] == '>' || (*c)[i] == '<') && (*c)[i + 1] && \
				(*c)[i + 1] == '&' && (*c)[i + 2]
			&& ((*c)[i + 2] != '-' || !ft_isdigit((*c)[i + 2])))
			return (0);
	}
	return (1);
}

int			pushback_aggreg(t_fdlist **flist, int fd_in, int fd_out)
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

int			hub_aggreg(char **cmd)
{
	FT_INIT(int, fd_in, 0);
	FT_INIT(int, fd_out, 0);
	FT_INIT(t_fdlist *, tmp, NULL);
	FT_INIT(t_fdlist *, tmp_start, NULL);
	if (!start_aggreg(&(*cmd), &fd_in, &fd_out, &tmp))
		return (0);
	tmp_start = tmp;
	while (tmp->next)
		tmp = tmp->next;
	if (!pushback_aggreg(&g_shell.aggreg, tmp->fd_in, tmp->fd_file))
		return (free_tmp_aggreg(&tmp_start));
	if (!tmp->prev)
		return (free_tmp_aggreg(&tmp_start));
	tmp = tmp->prev;
	while (tmp)
	{
		if (!fd_already_in_fdlist(&g_shell.aggreg, tmp->fd_in))
			if (!pushback_aggreg(&g_shell.aggreg, tmp->fd_in, tmp->fd_file))
				return (free_tmp_aggreg(&tmp_start));
		if (!tmp->prev)
			break ;
		tmp = tmp->prev;
	}
	free_tmp_aggreg(&tmp_start);
	return (1);
}

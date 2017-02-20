/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggreg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 13:01:44 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/13 12:37:19 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/21sh.h"

int			detect_numbers(char *cmd, int i)
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

int		replace_cmd_aggreg(char **cmd, int i, int j)
{
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp_replace, NULL);
	while ((*cmd)[i] && (*cmd)[i + 1] && ft_isdigit((*cmd)[i]))
		i++;
	if ((*cmd)[i] && !ft_isdigit((*cmd)[i]) && (*cmd)[i] != '-')
		i--;
	tmp = ft_strsub((*cmd), j, i - j + 1);
	tmp_replace = ft_str_replace((*cmd), tmp, "");
	ft_strdel(&(*cmd));
	(*cmd) = ft_strdup(tmp_replace);
	ft_strdel(&tmp);
	ft_strdel(&tmp_replace);
	return (1);
}

int			detect_aggreg(char **cmd, int *fd_in, int *fd_out)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	while ((*cmd)[i])
	{
		if (((*cmd)[i] == '>' || (*cmd)[i] == '<') && (*cmd)[i + 1] && (*cmd)[i + 1] == '&' && (*cmd)[i + 2]
			&& ((*cmd)[i + 2] == '-' || ft_isdigit((*cmd)[i + 2])))
		{
			if ((*cmd)[i - 1] && ft_isdigit((*cmd)[i - 1]))
			{
				j = i - 1;
				while ((*cmd)[j] && j >= 0 && ft_isdigit((*cmd)[j]))
					j--;
				(*fd_in) = detect_numbers((*cmd), ++j);
			}
			(*fd_out) = ft_isdigit((*cmd)[i + 2]) ? detect_numbers((*cmd), i + 2) : -1;
			return (replace_cmd_aggreg(cmd, i + 2, j));
		}
		else if (((*cmd)[i] == '>' || (*cmd)[i] == '<') && (*cmd)[i + 1] && (*cmd)[i + 1] == '&' && (*cmd)[i + 2]
			&& ((*cmd)[i + 2] != '-' || !ft_isdigit((*cmd)[i + 2])))
			return (0);
		i++;
	}
	return (1);
}

int			hub_aggreg(char **cmd)
{
	if (!detect_aggreg(&(*cmd), &g_shell.aggreg_fd_in,
		&g_shell.aggreg_fd_out))
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 15:18:50 by sgaudin           #+#    #+#             */
/*   Updated: 2017/04/10 14:58:48 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh42.h"

void		nav_to_delete_redir(char *str, int *i, int *j)
{
	while (str[(*i)] && str[(*i)] != ' ')
		(*i)--;
	(*j) = (*i);
	while (str[(*j)] && str[(*j) - 1] != '>')
		(*j)++;
	if (str[(*j)] == '>')
		(*j)++;
	while (str[(*j)] && str[(*j)] == ' ')
		(*j)++;
	while (str[(*j)] && str[(*j)] != ' ')
		(*j)++;
}

char		*delete_right_redirs_str(char *str)
{
	FT_INIT(int, i, 0);
	FT_INIT(int, j, 0);
	FT_INIT(char *, tmp, NULL);
	FT_INIT(char *, tmp2, NULL);
	while (str && i < (int)ft_strlen(str))
	{
		if (str[i] == '>')
		{
			nav_to_delete_redir(str, &i, &j);
			tmp2 = ft_strsub(str, i, j - i);
			tmp = ft_str_replace(str, tmp2, "");
			ft_strdel(&tmp2);
			ft_strdel(&str);
			str = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
		i++;
	}
	return (str);
}

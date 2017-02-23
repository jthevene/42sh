/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:25:05 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/12 15:25:07 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		unfinished_quote(char *line)
{
	FT_INIT(int, sq, 0);
	FT_INIT(int, dq, 0);
	FT_INIT(int, i, -1);
	while (line[++i])
	{
		if (line[i] == '\'')
		{
			sq = 1;
			i = unfinished_squote(line, i);
			if (line[i] == '\'')
				sq = 0;
		}
		else if (line[i] == '\"')
		{
			dq = 1;
			i = unfinished_dquote(line, i);
			if (line[i] == '\"')
				dq = 0;
		}
	}
	if (sq == 1)
		return (1);
	else if (dq == 1)
		return (2);
	return (0);
}

int		unfinished_squote(char *line, int i)
{
	i++;
	while (i < (int)ft_strlen(line) && line[i] != '\'' && line[i])
		i++;
	return (i);
}

int		unfinished_dquote(char *line, int i)
{
	i++;
	while (i < (int)ft_strlen(line) && line[i] != '\"' && line[i])
		i++;
	return (i);
}

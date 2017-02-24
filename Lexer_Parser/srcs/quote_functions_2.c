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
	FT_INIT(int, bq, 0);
	FT_INIT(int, aco, 0);
	FT_INIT(int, cro, 0);
	FT_INIT(int, par, 0);
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
		else if (line[i] == '`')
		{
			bq = 1;
			i = unfinished_bquote(line, i);
			if (line[i] == '`')
				bq = 0;
		}
		else if (line[i] == '{')
		{
			aco = 1;
			i = unfinished_aco(line, i);
			if (line[i] == '}')
				aco = 0;
		}
		else if (line[i] == '[')
		{
			cro = 1;
			i = unfinished_cro(line, i);
			if (line[i] == ']')
				cro = 0;
		}
		else if (line[i] == '(')
		{
			par = 1;
			i = unfinished_par(line, i);
			if (line[i] == ')')
				par = 0;
		}
	}
	if (sq == 1)
		return (1);
	else if (dq == 1)
		return (2);
	else if (bq == 1 || aco == 1 || cro == 1 || par == 1)
		return (3);
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

int		unfinished_bquote(char *line, int i)
{
	i++;
	while (i < (int)ft_strlen(line) && line[i] != '`' && line[i])
		i++;
	return (i);
}

int		unfinished_aco(char *line, int i)
{
	i++;
	while (i < (int)ft_strlen(line) && line[i] != '}' && line[i])
		i++;
	return (i);
}

int		unfinished_cro(char *line, int i)
{
	i++;
	while (i < (int)ft_strlen(line) && line[i] != ']' && line[i])
		i++;
	return (i);
}

int		unfinished_par(char *line, int i)
{
	i++;
	while (i < (int)ft_strlen(line) && line[i] != ')' && line[i])
		i++;
	return (i);
}

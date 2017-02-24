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

int		unfinished_parenthesis(char *line, int i, int *var, char to_find)
{
	(*var) = 1;
	i++;
	while (i < (int)ft_strlen(line) && line[i] != to_find && line[i])
		i++;
	if (line[i] == to_find)
		(*var) = 0;
	return (i);
}

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
			i = unfinished_parenthesis(line, i, &sq, '\'');
		else if (line[i] == '\"')
			i = unfinished_parenthesis(line, i, &dq, '\"');
		else if (line[i] == '`')
			i = unfinished_parenthesis(line, i, &bq, '`');
		else if (line[i] == '{')
			i = unfinished_parenthesis(line, i, &aco, '}');
		else if (line[i] == '[')
			i = unfinished_parenthesis(line, i, &cro, ']');
		else if (line[i] == '(')
			i = unfinished_parenthesis(line, i, &par, ')');
	}
	if (sq == 1)
		return (1);
	else if (dq == 1)
		return (2);
	else if (bq == 1 || aco == 1 || cro == 1 || par == 1)
		return (3);
	return (0);
}

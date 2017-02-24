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

int			unfinished_parenthesis(char *line, int i, int *var, char to_find)
{
	(*var) = 1;
	i++;
	while (i < (int)ft_strlen(line) && line[i] != to_find && line[i])
		i++;
	if (line[i] == to_find)
		(*var) = 0;
	return (i);
}

t_quotes	*init_quotes_struct(void)
{
	t_quotes *quotes;

	if (!(quotes = (t_quotes *)malloc(sizeof(t_quotes))))
		return (NULL);
	quotes->sq = 0;
	quotes->dq = 0;
	quotes->bq = 0;
	quotes->aco = 0;
	quotes->cro = 0;
	quotes->par = 0;
	return (quotes);
}

int			free_quotes(t_quotes **quotes, int val_to_return)
{
	free((*quotes));
	return (val_to_return);
}

int			unfinished_quote(char *line)
{
	FT_INIT(t_quotes, *quotes, init_quotes_struct());
	FT_INIT(int, i, -1);
	while (line[++i])
	{
		if (line[i] == '\'')
			i = unfinished_parenthesis(line, i, &quotes->sq, '\'');
		else if (line[i] == '\"')
			i = unfinished_parenthesis(line, i, &quotes->dq, '\"');
		else if (line[i] == '`')
			i = unfinished_parenthesis(line, i, &quotes->bq, '`');
		else if (line[i] == '{')
			i = unfinished_parenthesis(line, i, &quotes->aco, '}');
		else if (line[i] == '[')
			i = unfinished_parenthesis(line, i, &quotes->cro, ']');
		else if (line[i] == '(')
			i = unfinished_parenthesis(line, i, &quotes->par, ')');
	}
	if (quotes->sq == 1)
		return (free_quotes(&quotes, 1));
	else if (quotes->dq == 1)
		return (free_quotes(&quotes, 2));
	else if (quotes->bq == 1 || quotes->aco == 1 
		|| quotes->cro == 1 || quotes->par == 1)
		return (free_quotes(&quotes, 3));
	return (free_quotes(&quotes, 0));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjacque <hjacque@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:41 by hjacque           #+#    #+#             */
/*   Updated: 2017/03/08 14:45:48 by hjacque          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		token_squote(t_token *token, char *line, int pos, int i)
{
	token->type = SQUOTE;
	i = pos;
	pos++;
	while (line[pos] != '\'')
		pos++;
	pos++;
	pos = get_lexeme_pos(line, pos);
	add_lexeme(token, line, pos, i);
	return (pos);
}

int		token_dquote(t_token *token, char *line, int pos, int i)
{
	token->type = DQUOTE;
	i = pos;
	pos++;
	while (line[pos] != '\"')
		pos++;
	pos++;
	pos = get_lexeme_pos(line, pos);
	add_lexeme(token, line, pos, i);
	return (pos);
}

char	*finish_quotes(char *line)
{
	FT_INIT(int, i, 1);
	FT_INIT(char*, tmp, ft_strdup(line));
	while (i != 0)
	{
		i = unfinished_quote(tmp);
		if (i == 1)
			tmp = finish_the_squote(tmp);
		else if (i == 2)
			tmp = finish_the_dquote(tmp);
		else if (i == 3)
			tmp = finish_line_backslash(tmp);
	}
	return (tmp);
}

t_token	*get_token(t_token *token, int type)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == type)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

int		compare_end(char *str1, char *str2)
{
	FT_INIT(int, i, ft_strlen(str1));
	FT_INIT(int, e, i - 2);
	FT_INIT(int, x, 0);
	while (e >= 0 && str1[e] && str2[x] && str2[x] == str1[e])
	{
		x++;
		e++;
	}
	if (e == i)
		return (1);
	return (0);
}

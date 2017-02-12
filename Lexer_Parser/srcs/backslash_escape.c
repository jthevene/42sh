/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash_escape.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:23:16 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/12 15:23:18 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	backslash_char(t_token *token)
{
	FT_INIT(int, pos, 0);
	FT_INIT(int, s, 0);
	FT_INIT(int, d, 0);
	while (token->lexeme[pos])
	{
		if (token->lexeme[pos] == '\'')
			pos = supp_squote(token, pos, s);
		else if (token->lexeme[pos] == '\"')
			pos = supp_dquote(token, pos, d);
		else if (token->lexeme[pos] == '\\')
		{
			ft_memmove(&(token->lexeme[pos]), \
				&(token->lexeme[pos + 1]), ft_strlen(token->lexeme) - pos);
			pos++;
		}
		pos++;
	}
}

int		supp_squote(t_token *token, int pos, int s)
{
	s = pos;
	ft_memmove(&(token->lexeme[s]), \
		&(token->lexeme[s + 1]), ft_strlen(token->lexeme) - s);
	while (token->lexeme[pos] != '\'')
		pos++;
	ft_memmove(&(token->lexeme[pos]), \
		&(token->lexeme[pos + 1]), ft_strlen(token->lexeme) - pos);
	pos++;
	return (pos);
}

int		supp_dquote(t_token *token, int pos, int d)
{
	d = pos;
	ft_memmove(&(token->lexeme[d]), \
		&(token->lexeme[d + 1]), ft_strlen(token->lexeme) - d);
	while (token->lexeme[pos] != '\"')
		pos++;
	ft_memmove(&(token->lexeme[pos]), \
		&(token->lexeme[pos + 1]), ft_strlen(token->lexeme) - pos);
	pos++;
	return (pos);
}

int		get_lexeme_pos(char *line, int pos)
{
	int		exit;

	exit = 0;
	while (!exit)
	{
		while (ft_isprintnotope(line[pos]) == 1)
			pos++;
		pos = quote_in_word(line, pos);
		if (ft_isprintnotope(line[pos]) == 0)
			exit = 1;
	}
	return (pos);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:40 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/13 10:15:57 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

t_token		*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->lexeme = NULL;
	token->next = NULL;
	return (token);
}

int			fd_redir(t_token *token, char *line, int pos)
{
	FT_INIT(int, i, 1);
	FT_INIT(int, x, pos);
	while (ft_isdigit((unsigned char)line[pos + i]))
		i++;
	if (line[pos + i] == '>' && line[pos + i + 1] == '>')
	{
		pos = pos + i + 2;
		token->type = DMORE;
		add_lexeme(token, line, pos, x);
		return (pos);
	}
	else if (line[pos + i] == '>')
	{
		pos = pos + i + 1;
		token->type = MORE;
		add_lexeme(token, line, pos, x);
		return (pos);
	}
	return (pos);
}

int			words_token(t_token *token, char *line, int pos, int i)
{
	token->type = WORDS;
	i = pos;
	pos = get_lexeme_pos(line, pos);
	add_lexeme(token, line, pos, i);
	if (str_is_digit(token->lexeme) == 1)
		token->type = FDIGIT;
	return (pos);
}

int			lire_lexeme_2(t_token *token, char *line, int pos, int i)
{
	FT_INIT(int, x, pos);
	if (ft_isdigit(line[pos]))
	{
		pos = fd_redir(token, line, pos);
		if (x != pos)
			return (pos);
	}
	if (ft_isprintnotope(line[pos]) == 1)
		return (words_token(token, line, pos, i));
	if (ft_isope(line[pos]) >= 1)
		return (check_ope(token, line, pos, i));
	return (pos);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_distrib.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <sgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:36:41 by hjacque           #+#    #+#             */
/*   Updated: 2017/04/13 10:16:17 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	lexer_parser(char *line)
{
	FT_INIT(t_all, *all, NULL);
	FT_INIT(int, o, 0);
	if (!(all = init_all_struct(line)))
		return ;
	if ((ft_strcmp(all->line, "\0") != 0) && (isallspace(all->line) != 1))
	{
		all->line = trim_end(all->line);
		o = ft_strlen(all->line);
		if ((all->line[o - 1] == '\\') || (compare_end(all->line, "||")) \
			|| (all->line[o - 1] == '|') || (compare_end(all->line, "&&")))
			all->line = finish_line_backslash(all->line);
		ft_newhist(all->line);
		analise_line(all);
		check_for_hdoc(all->tokens_begin);
		send_token_to_glob(all);
		remove_bslash_quotes(all->tokens_begin);
		start_parse(all->tokens_begin);
	}
	free(all->line);
	free(all);
	ft_strdel(&line);
}

void	analise_line(t_all *all)
{
	int			pos;
	t_token		*token;

	token = init_token();
	pos = 0;
	all->tokens_begin = token;
	while (all->line[pos])
	{
		pos = lire_lexeme(token, all->line, pos);
		if (all->line[pos])
		{
			token->next = init_token();
			token = token->next;
		}
	}
}

int		lire_lexeme(t_token *token, char *line, int pos)
{
	FT_INIT(int, i, 0);
	while (line[pos] == ' ' || line[pos] == '\t')
		pos++;
	FT_INIT(int, x, pos);
	if (line[pos] == '\'')
		return (token_squote(token, line, pos, i));
	if (line[pos] == '\"')
		return (token_dquote(token, line, pos, i));
	if (ft_isope(line[pos]) == 2 || ft_isope(line[pos]) == 3)
	{
		pos = check_for_aggreg(token, line, pos);
		if (x != pos)
			return (pos);
	}
	if (ft_isdigit(line[pos]))
	{
		pos = check_for_aggreg_fd(token, line, pos);
		if (x != pos)
			return (pos);
	}
	return (lire_lexeme_2(token, line, pos, i));
}

void	add_lexeme(t_token *token, char *line, int pos, int i)
{
	token->lexeme = ft_strndup(&(line[i]), pos - i);
}

int		ft_isope(char c)
{
	if (c == '&')
		return (1);
	else if (c == '<')
		return (2);
	else if (c == '>')
		return (3);
	else if (c == '|')
		return (4);
	else if (c == ';')
		return (5);
	return (0);
}

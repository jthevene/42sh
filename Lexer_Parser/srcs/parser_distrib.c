/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_distrib.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 15:24:36 by sgaudin           #+#    #+#             */
/*   Updated: 2017/02/12 15:24:38 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	lexer_parser(char *line)
{
	t_all	*all;

	FT_INIT(int, o, 0);
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		return ;
	all->line = ft_strdup(line);
	all->line = finish_quotes(all->line);
	if ((ft_strcmp(all->line, "\0") == 0) || (isallspace(all->line) == 1))
		;
	else
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
	if (line[pos] == '\'')
		pos = token_squote(token, line, pos, i);
	if (line[pos] == '\"')
		pos = token_dquote(token, line, pos, i);
	if (ft_isdigit(line[pos]))
		pos = check_for_aggreg_fd(token, line, pos);
	if (ft_isope(line[pos]) == 2 || ft_isope(line[pos]) == 3)
		pos = check_for_aggreg(token, line, pos);
	if (ft_isprintnotope(line[pos]) == 1)
	{
		token->type = WORDS;
		i = pos;
		pos = get_lexeme_pos(line, pos);
		printf("i = %d\npos = %d\n", i, pos);
		add_lexeme(token, line, pos, i);
		if (str_is_digit(token->lexeme) == 1)
			token->type = FDIGIT;
		//backslash_char(token);
	}
	else if (ft_isope(line[pos]) >= 1)
		pos = check_ope(token, line, pos, i);
	return (pos);
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

#include "../includes/sh.h"

void		lexer_parser(char *line)
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
		if (all->line[o - 1] == '\\')
			all->line = finish_line_backslash(all->line);
		analise_line(all);
		print_tokens(all->tokens_begin);
		send_token_to_glob(all);
		start_parse(all->tokens_begin);
	}
	free(all->line);
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
		pos = lire_lexeme(token, all->line , pos);
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
	else if (line[pos] == '\"')
		pos = token_dquote(token, line, pos, i);
	else if (ft_isprintnotope(line[pos]) == 1)
	{
		token->type = WORDS;
		i = pos;
		pos = get_lexeme_pos(line, pos);
		add_lexeme(token, line, pos, i);
		backslash_char(token);
	}
	else if (ft_isope(line[pos]) >= 1)
		pos = check_ope(token, line, pos, i);
	return (pos);
}

void	add_lexeme(t_token *token, char *line, int pos, int i)
{
	token->lexeme = ft_strndup(&(line[i]), pos - i);
}

int        ft_isope(char c)
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

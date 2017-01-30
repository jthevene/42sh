#include "../includes/sh.h"

void		lexer_parser(char *line)
{
	t_all	*all;
	int		i;
	int		u;
	int		o;

	u = 0;
	if (!(all = (t_all *)malloc(sizeof(t_all))))
		return ;
	all->line = ft_strdup(line);
	i = 5;
	while (i != 0)
	{
		i = unfinished_quote(all->line);
		if (i == 1)
			all->line = finish_the_squote(all->line);
		else if (i == 2)
			all->line = finish_the_dquote(all->line);
	}
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
		printf("\n***NEW_TOKEN***\n");
		printf("pos = %d\n", pos);
		pos = lire_lexeme(token, all->line , pos);
		printf("1 token lu\n");
		if (all->line[pos])
		{
			printf("NOP\n");
			token->next = init_token();
			token = token->next;
		}
		printf("next token\n");
	}
}

int		lire_lexeme(t_token *token, char *line, int pos)
{
	int		i;

	i = 0;
	while (line[pos] == ' ' || line[pos] == '\t')
		pos++;
	if (line[pos] == '\'')
	{
		printf("\n***SQUOTE***\n");
		pos++;
		token->type = SQUOTE;
		i = pos;
		while (line[pos] != '\'')
			pos++;
		add_lexeme(token, line, pos, i);
		pos++;
	}
	else if (line[pos] == '\"')
	{
		printf("\n***DQUOTE***\n");
		pos++;
		token->type = DQUOTE;
		i = pos;
		while (line[pos] != '\"')
			pos++;
		add_lexeme(token, line, pos, i);
		pos++;
	}		
	else if (ft_isprintnotope(line[pos]) == 1)
	{
		printf("\n***WORDS***\n");
		printf("pos = %d\n", pos);
		token->type = WORDS;
		i = pos;
		pos = get_lexeme_pos(line, pos);
		add_lexeme(token, line, pos, i);
		backslash_char(token);
	}
	else if (ft_isope(line[pos]) >= 1)
	{
		printf("\n***OPE***\n");
		pos = check_ope(token, line, pos, i);
	}
	return (pos);
}

void	add_lexeme(t_token *token, char *line, int pos, int i)
{
	token->lexeme = ft_strndup(&(line[i]), pos - i);
	printf("type = %d\n", token->type);
	printf("lexeme = %s\n", token->lexeme);
	printf("lexeme good\n");
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

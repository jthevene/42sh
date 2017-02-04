#include "../includes/sh.h"

int		token_squote(t_token *token, char *line, int pos, int i)
{
	pos++;
	token->type = SQUOTE;
	i = pos;
	while (line[pos] != '\'')
		pos++;
	add_lexeme(token, line, pos, i);
	pos++;
	return (pos);
}

int		token_dquote(t_token *token, char *line, int pos, int i)
{
	pos++;
	token->type = DQUOTE;
	i = pos;
	while (line[pos] != '\"')
		pos++;
	add_lexeme(token, line, pos, i);
	pos++;
	return (pos);
}

char	*finish_quotes(char *line)
{
	FT_INIT(int, i, 1);
	FT_INIT(char*, tmp, NULL);
	while (i != 0)
	{
		i = unfinished_quote(line);
		if (i == 1)
			tmp = finish_the_squote(line);
		else if (i == 2)
			tmp = finish_the_dquote(line);
	}
	free(line);
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
